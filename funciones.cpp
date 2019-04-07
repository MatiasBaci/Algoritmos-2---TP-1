// funciones del programa
#include "funciones.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream> // es necesario todo esto?
using namespace std;
//const int FRECUENCIA_MUESTRAS = 44100;
//const float FREQ_A4 = 440;
//const int MASCARA = 255;


//void obtener_nota(string nota_y_duracion, string *vector[]) {
//    
//    string nota;
//    string duracion_str;
//    int duracion;
//    int separacion;
//    
//    separacion = nota_y_duracion.find(" ");
//    nota = nota_y_duracion.substr(0, separacion - 1);
//    duracion_str = nota_y_duracion.substr(separacion + 1);
//    duracion = string_a_int(duracion_str);
//    vector[0] = nota;
//    vector[1] = duracion_str;
//}


int distancia_semitonos(string nota){
			
	//int octava = (int) nota.back();
	int octava = nota[nota.length()-1] - 48;
	//nota.pop_back();
	nota.erase(nota.length()-1);
	int distancia = 12 * (octava - 4);
			
	if 		(nota == "B")  distancia += 2;
	else if (nota == "A#") distancia += 1;
	else if (nota == "A")  distancia += 0;
	else if (nota == "G#") distancia -= 1;
	else if (nota == "G")  distancia -= 2;
	else if (nota == "F#") distancia -= 3;
	else if (nota == "F")  distancia -= 4;
	else if (nota == "E")  distancia -= 5;
	else if (nota == "D#") distancia -= 6;
	else if (nota == "D")  distancia -= 7;
	else if (nota == "C#") distancia -= 8;
	else if (nota == "C")  distancia -= 9;
	
	return distancia;
}


float nota_a_frecuencia(string nota){ //hacer que traduzca notas en ASPN a frecuencias en Hz
    
	float freq;
    
    if (nota != "H") {
    	
		int distancia;
    	distancia = distancia_semitonos(nota); //la distancia de semitonos entre la nota y A4
	    freq = FREQ_A4 * pow(2, (float) distancia / 12 );
	}
	else freq = 0; //silencio
		
	return freq;
}


// f(x) = A sin(Bt+C) + D
int frec_a_sonido(float amplitud, float freq, float &t, float defasaje, int sample_rate, int bit_depth) { //x seria la x del muestreo anterior
    
	int altura = 0;
	if (bit_depth == 8) altura = amplitud;
	
    t = t + (float) (1 / (float) sample_rate);
    
    int valor = (int) ( amplitud * sin ( freq * t * 2 * 3.141592 + defasaje ) + altura );
    return valor;
}


int string_a_int(string cadena) {
	
	stringstream ss;
	ss << cadena;
    int entero;
    ss >> entero;
    return entero;
}


void escribir(ofstream &archivo_wav, int valor, int bit_depth) {
    
	int resultado;
	char c;
	int veces = bit_depth / 8;
	
	for(int i = 0; i < veces; i++) {
		
		resultado = valor & MASCARA;
		c = (char) resultado;
		archivo_wav << c;
		//
		cout << c;
		//
	    valor = valor >> 8;
	}
}


float sonido(ofstream& archivo_wav, string nota, int duracion, float defasaje, float amplitud, int sample_rate, int bit_depth) {
    
	float freq;
	freq = nota_a_frecuencia(nota);
	
	float t = 0;	
	while (t < (float) duracion) {
        escribir(archivo_wav, frec_a_sonido(amplitud, freq, t, defasaje, sample_rate, bit_depth), bit_depth);
    }
	defasaje = freq * t + defasaje;
    return defasaje;
}


void musica(ifstream& archivo_txt, ofstream& archivo_wav, float amplitud, int sample_rate, int bit_depth) {
	
	string nota_y_duracion;
	string nota;
	int duracion;
	stringstream ss;
	//string vector[2];
	float defasaje = 0;
	
	while (getline(archivo_txt, nota_y_duracion)) {
		
		//obtener_nota(nota_y_duracion, vector);
		//string nota;
	    string duracion_str;
	    //int duracion;
	    int separacion;
	    
	    separacion = nota_y_duracion.find("\t");
	    nota = nota_y_duracion.substr(0, separacion);
	    duracion_str = nota_y_duracion.substr(separacion);
	    duracion = string_a_int(duracion_str);
//	    vector[0] = nota;
//	    vector[1] = duracion_str;
		
		//ss << vector[1];
		//ss << nota;
		//ss >> duracion;
		
		//nota = vector[0];
		
		defasaje = sonido(archivo_wav, nota, duracion, defasaje, amplitud, sample_rate, bit_depth);
	}
}


int leer_int(ifstream& archivo_txt) {

	string aux;
    getline(archivo_txt, aux);
    
    int entero;
	entero = string_a_int(aux);
    
    return entero;
}


void escribir_str(ofstream &archivo_wav, string valor) {
	
	char p[valor.length()]; 
	
	for (int i = 0; i < sizeof(p); i++) {
		p[i] = valor[3-i];
		archivo_wav << p[i];
	}
}


int string_to_hex(string cadena) {
    unsigned int x;   
    std::stringstream ss;
    ss << std::hex << cadena;
    ss >> x;
    return x;
}


void escribir_chunk_header(ofstream &archivo_wav, int duracion_archivo, int bit_depth, int sample_rate) {
	
	escribir_str(archivo_wav, "RIFF");
	
	int tamanio_desde_byte8;
	tamanio_desde_byte8 = tamanio_data(duracion_archivo, bit_depth, sample_rate) + 36;
	escribir(archivo_wav, tamanio_desde_byte8, 32);
	
	escribir_str(archivo_wav, "WAVE");
}


void escribir_chunk_formato(ofstream &archivo_wav, int bit_depth, int sample_rate) {
	
	escribir_str(archivo_wav, "fmt ");
	
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

	escribir_str(archivo_wav, "data");
	
	int tamanio_datos_n;
	tamanio_datos_n = tamanio_data(duracion_archivo, bit_depth, 32);
	escribir(archivo_wav, tamanio_datos_n, bit_depth);
	
	musica(archivo_txt, archivo_wav, amplitud, sample_rate, bit_depth);
}


void EndianSwap32(char c[]) {
	
	unsigned char tmp;
    tmp  = c[0];
    c[0] = c[3];
    c[3] = tmp;
    tmp  = c[1];
    c[1] = c[2];
    c[2] = tmp;
}


int tamanio_data(int duracion_archivo, int bit_depth, int sample_rate) {
	
	int tamanio = (int) ( (float) duracion_archivo * (float) bit_depth / 8 * (float) sample_rate );
	return tamanio;
}
