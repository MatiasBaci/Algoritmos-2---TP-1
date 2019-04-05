// funciones del programa
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream> // es necesario todo esto?
using namespace std;
//const int FRECUENCIA_MUESTRAS = 44100;
const float FREQ_A4 = 440;
const int MASCARA = 255;


int distancia_semitonos(string nota){
			
	int octava = (int) nota.back();
	nota.pop_back();
	int distancia = 12 * (octava - 4);
	
	switch(nota){
			case "B":  distancia += 2; break;
			case "A#": distancia += 1; break;
			case "A":  distancia += 0; break;
			case "G#": distancia -= 1; break;
			case "G":  distancia -= 2; break;
			case "F#": distancia -= 3; break;
			case "F":  distancia -= 4; break;
			case "E":  distancia -= 5; break;
			case "D#": distancia -= 6; break;
			case "D":  distancia -= 7; break;
			case "C#": distancia -= 8; break;
			case "C":  distancia -= 9; break;
	}
	return distancia;
}


float nota_a_frecuencia(string nota){ //hacer que traduzca notas en ASPN a frecuencias en Hz
    
	float freq;
    
    if (nota != "H") {
    	
		int distancia;
    	distancia = distancia_semitonos(nota); //la distancia de semitonos entre la nota y A4
	    freq = FREQ_A4 * pow(2, (distancia / 12));
	}
	else freq = 0; //silencio
		
	return freq;
}


// f(x) = A sin(Bt+C) + D
int frec_a_sonido(float amplitud, float freq, float &t, float defasaje, int sample_rate, int altura_segun_bitdepth){ //x seria la x del muestreo anterior
    
	int valor;
	
    t = t + (float) (1 / sample_rate);
    valor = (int) ( amplitud * sin ( freq * t + defasaje ) + altura_segun_bitdepth );
    return valor;
}


float sonido(ofstream archivo_wav, string nota, int duracion, float defasaje, float amplitud) {
    
	float freq;
	freq = nota_a_frecuencia(nota);
	
	float t = 0;	
	while (t < (float) duracion) {
        escribir(archivo_wav, frec_a_sonido(amplitud, freq, t, defasaje, sample_rate, altura_segun_bitdepth), 4);
    }
	defasaje = freq * t + defasaje;
    return defasaje;
}


void musica(ifstream archivo_txt, ofstream archivo_wav, float amplitud, int sample_rate, int bit_depth) {
	
	string nota_y_duracion;
	string nota;
	int duracion;
	stringstream ss;
	string vector[2];
	float defasaje = 0;
	
	while (getline(archivo_txt, nota_y_duracion)) {
		
		obtener_nota(nota_y_duracion, &vector[]);
		
		ss << vector[1];
		ss >> duracion;
		
		nota = vector[0];
		
		defasaje = sonido(archivo_wav, nota, duracion, defasaje, amplitud)
	}
}


void obtener_nota(string nota_y_duracion, string &vector[]) {
    
    string nota;
    string duracion_str;
    int duracion;
    int separacion;
    
    separacion = nota_y_duracion.find(" ");
    nota = nota_y_duracion.substr(0, separacion - 1);
    duracion_str = nota_y_duracion.substr(separacion + 1);
    duracion = (int) duracion_str;
    vector[0] = nota;
    vector[1] = duracion_str;
}


int leer_int(ifstream archivo_txt) {

	string aux;
    getline(archivo_txt, aux);
    
    stringstream ss;
    ss << aux;
    
    int entero;
    ss >> entero;
    
    return entero;
}


void escribir(ofstream archivo_wav, int valor, int bit_depth) {
    
	int resultado;
	char c;
	int veces = bit_depth / 8;
	
	for(int i = 0; i < veces; i++) {
		
		resultado = valor & MASCARA;
		c = (char) resultado;
		archivo_wav << c;
	    valor = valor >> 8;
	}
}


int string_to_hex(string cadena) {
    unsigned int x;   
    std::stringstream ss;
    ss << std::hex << cadena;
    ss >> x;
    return x;
}


void escribir_chunk_header(ifstream archivo_txt, int duracion_archivo, int bit_depth, int sample_rate) {
	
	escribir(archivo_txt, "RIFF", 4);
	
	int tamanio_desde_byte8;
	tamanio_desde_byte8 = tamanio_del_archivo(duracion_archivo, bit_depth, sample_rate) - 8;
	escribir(archivo_txt, tamanio_desde_byte8, 4);
	
	escribir(archivo_txt, "WAVE", 4);
}

void escribir_chunk_formato(archivo_txt, int bit_depth, int sample_rate) {
	
	escribir(archivo_txt, "fmt ", 4);
	
	escribir(archivo_txt, 16);
	
	int formato_del_audio = 1; //1 = sin compresion
	escribir(archivo_txt, formato_del_audio);
	
	int cantidad_de_canales = 1; //1 = mono
	escribir(archivo_txt, cantidad_de_canales);
	
	escribir(archivo_txt, sample_rate);
	
	int byte_rate = sample_rate * cantidad_de_canales * bit_depth / 8;
	escribir(archivo_txt, byte_rate;
	
	int block_align = cantidad_de_canales * bit_depth / 8;
	escribir(archivo_txt, block_align);
	
	escribir(archivo_txt, bit_depth);
}


void escribir_chunk_data(float amplitud, int sample_rate, int bit_depth, archivo, int tamanio_archivo) {

	escribir(archivo, "data", 4);
	
	int tamanio_datos_n;
	tamanio_datos_n = tamanio_archivo - 52;
	escribir(archivo, tamanio_datos_n);
	
	musica(amplitud, sample_rate, bit_depth, archivo);
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


int tamanio_del_archivo(int duracion_archivo, int bit_depth, int sample_rate) {
	
	int tamanio = duracion_archivo * bit_depth * sample_rate;
	return tamanio;
}
