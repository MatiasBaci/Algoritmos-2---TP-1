#include "funciones.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>
using namespace std;


int leer_duracion(ifstream& archivo_txt) {
//obtiene la duracion de la melodia (primer linea del .txt) en milisegundos
	string aux;
    getline(archivo_txt, aux);
    
    int entero;
	entero = string_a_int(aux);
    
    return entero;
}


int string_a_int(string cadena) {
//convierte un string en un entero
	stringstream ss;
	ss << cadena;
    int entero;
    ss >> entero;
    return entero;
}


void escribir_chunk_header(ofstream &archivo_wav, int duracion_archivo, int bit_depth, int sample_rate) {
//escribe la informacion del header al .wav
	archivo_wav << "RIFF";
		
	int tamanio_desde_byte8;
	tamanio_desde_byte8 = tamanio_data(duracion_archivo, bit_depth, sample_rate) + 36;
	escribir(archivo_wav, tamanio_desde_byte8, 32);
	
	archivo_wav << "WAVE";
}


int tamanio_data(int duracion_archivo, int bit_depth, int sample_rate) {
//calcula el tamanio de los datos
	int tamanio = (int) ( (float) duracion_archivo / 1000 * (float) bit_depth / 8 * (float) sample_rate );
	return tamanio;
}


void escribir(ofstream &archivo_wav, int valor, int bit_depth) {
//escribe el valor numerico obtenido al archivo .wav en HEX
	int resultado;
	char c;
	int bytes = bit_depth / 8;
	
	for(int i = 1; i <= bytes; i++) {
//	la cantidad de veces que se ejecuta depende de los bytes que va a ocupar el valor
		resultado = valor & MASCARA;
//		c = (char) resultado;
//		archivo_wav << c;
		archivo_wav.write((const char*) &resultado, 1);
	    valor = valor >> 8;
	}
}


void escribir_chunk_formato(ofstream &archivo_wav, int bit_depth, int sample_rate) {
//escribe la informacion de formato al .wav
	archivo_wav << "fmt ";
		
	escribir(archivo_wav, 16, 32);
	
	int formato_del_audio = 1; //1 = sin compresion
	escribir(archivo_wav, formato_del_audio, 16);
	
	int cantidad_de_canales = 1; //1 = mono
	escribir(archivo_wav, cantidad_de_canales, 16), bit_depth;
	
	escribir(archivo_wav, sample_rate, 32);
	
	int byte_rate = sample_rate * cantidad_de_canales * bit_depth / 8;
	escribir(archivo_wav, byte_rate, 32);
	
	int block_align = cantidad_de_canales * bit_depth / 8;
	escribir(archivo_wav, block_align, 16);
	
	escribir(archivo_wav, bit_depth, 16);
}


void escribir_chunk_data(ifstream &archivo_txt, ofstream &archivo_wav, float amplitud, int sample_rate, int bit_depth, int duracion_archivo) {
//escribe los datos al .wav
	archivo_wav << "data";
	
	int tamanio_datos_n;
	tamanio_datos_n = tamanio_data(duracion_archivo, bit_depth, sample_rate);
	escribir(archivo_wav, tamanio_datos_n, 32);
	
	musica(archivo_txt, archivo_wav, amplitud, sample_rate, bit_depth);	
}


void musica(ifstream& archivo_txt, ofstream& archivo_wav, float amplitud, int sample_rate, int bit_depth) {
//lee cada linea del .txt y escribe al .wav
	string nota_y_duracion;
	string nota;
	int duracion;
	float defasaje = 0;
	
	while (getline(archivo_txt, nota_y_duracion)) {
	//ciclo que resuelve para cada linea, es decir, para cada nota de la melodia
	    string duracion_str;
	    int separacion;
	    
	    separacion = nota_y_duracion.find("\t");
	    nota = nota_y_duracion.substr(0, separacion);
	    duracion_str = nota_y_duracion.substr(separacion);
	    duracion = string_a_int(duracion_str);

		defasaje = sonido(archivo_wav, nota, duracion, defasaje, amplitud, sample_rate, bit_depth);
	}
}


float sonido(ofstream& archivo_wav, string nota, int duracion, float defasaje, float amplitud, int sample_rate, int bit_depth) {
//obtiene la frecuencia de la nota, la usa para escribir al .wav, y devuelve el defasaje para la proxima nota
	float freq;
	freq = nota_a_frecuencia(nota);
	
	float t = 0;	
	while (t < (float) duracion / 1000) {
		//ciclo que escribe cada sample
        escribir(archivo_wav, frec_a_sonido(amplitud, freq, t, defasaje, sample_rate, bit_depth), bit_depth);
    }
	defasaje = 2 * M_PI * freq * t + defasaje;
    return defasaje;
}


float nota_a_frecuencia(string nota) {
//obtiene la frecuencia en Hz a partir de la nota previamente leida del .txt    
	float freq;
    
    if (nota != "H") {
    	
		int distancia;
    	distancia = distancia_semitonos(nota); //la distancia de semitonos entre la nota y A4
	    freq = FREQ_A4 * pow(2, (float) distancia / 12 );
	}
	else freq = 0; //silencio
		
	return freq;
}


int distancia_semitonos(string nota) {
//obtiene el salto de semitonos entre la nota base A4 y la nota leida del .txt
	int octava = nota[nota.length()-1] - 48;
	nota.erase(nota.length()-1);
	int distancia = 12 * (octava - 4);
			
	if 		(nota == "B")  					distancia += 2;
	else if (nota == "A#" || nota == "Bb") 	distancia += 1;
	else if (nota == "A")  					distancia += 0;
	else if (nota == "G#" || nota == "Ab") 	distancia -= 1;
	else if (nota == "G")  					distancia -= 2;
	else if (nota == "F#" || nota == "Gb") 	distancia -= 3;
	else if (nota == "F")  					distancia -= 4;
	else if (nota == "E")  					distancia -= 5;
	else if (nota == "D#" || nota == "Eb") 	distancia -= 6;
	else if (nota == "D")  					distancia -= 7;
	else if (nota == "C#" || nota == "Db") 	distancia -= 8;
	else if (nota == "C")  					distancia -= 9;
	
	return distancia;
}


int frec_a_sonido(float amplitud, float freq, float &t, float defasaje, int sample_rate, int bit_depth) {
//calcula el valor que se debe escribir al .wav para un sample
// f(t) = A sin( B t + C ) + D
	int altura = 0;
	if (bit_depth == 8) altura = amplitud;
	
    t = t + (float) (1 / (float) sample_rate);
    
    int valor = (int) ( amplitud * sin ( 2 * M_PI * freq * t + defasaje ) + altura );
    return valor;
}

