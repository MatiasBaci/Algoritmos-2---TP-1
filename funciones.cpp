// funciones del programa
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream> // es necesario todo esto?
using namespace std;
//const int FRECUENCIA_MUESTRAS = 44100;
const float FREQ_A4 = 440;


int distancia_semitonos(string nota){
	
	if (nota != "H") {
		
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
	else return 0;
}


float nota_a_frecuencia(string nota){ //hacer que traduzca notas en ASPN a frecuencias en Hz
    float freq;
    int distancia = distancia_semitonos(nota); //la distancia de semitonos entre la nota y A4
    freq = FREQ_A4 * pow(2, (distancia / 12));
    return freq;
}


// f(x) = A sin(Bx+C) + D
int frec_a_sonido(float amplitud, float freq, float &x, float defasaje, int sample_rate, int altura_segun_bitdepth){ //x seria la x del muestreo anterior
    
	int valor;
    x = x + (float) (1 / sample_rate);
    valor = (int) ( amplitud * sin ( freq * x + defasaje ) + altura_segun_bitdepth );
    return valor;
}


float sonido(string nota, int duracion, float defasaje, float amplitud, int freq) {
    frecuencia = nota_a_frecuencia(nota);
    float x = 0;
    while (x < (float) duracion) { //esto depende de las unidades de "duracion"
        escribir_archivo(frec_a_sonido(amplitud, freq, x, defasaje));
    }
    defasaje = freq * x + defasaje;
    return defasaje;
}


void musica(float amplitud, int sample_rate, int bit_depth, archivo) {
	
	string nota_y_duracion;

	while getline(archivo, nota_y_duracion) {
		
		
	}
}


void leer_archivo(string nota_y_duracion, vector[]) { //aca quiero que lea 2 lineas de archivo y lo guarde en un vector.
    //una linea para la nota y otra la duracion
    string nota;
    string duracion_str;
    int duracion;
    int separacion;
    
    separacion = nota_y_duracion.find(" ");
    nota = nota_y_duracion.substr(0, separacion-1);
    duracion_str = nota_y_duracion.substr(separacion+1, 10);
    duracion = (int) duracion_str;
    vector[0] = nota;
    vector[1] = duracion;
}


void escribir_archivo(archivo, unsigned long valor) {
    archivo << valor;
}


int string_to_hex(string cadena) {
    unsigned int x;   
    std::stringstream ss;
    ss << std::hex << cadena;
    ss >> x;
    return x;
}


void escribir_header(archivo, int tamanio_desde_byte8) {
	escribir(archivo, "RIFF", 4);
	escribir(archivo, tamanio_desde_byte8, 4);
	escribir(archivo, "WAVE", 4);
}

void escribir_formato(archivo, int sample_rate) {
	
	escribir(archivo, "fmt ", 4);
	
	escribir(archivo, 16, 4);
	
	int formato_del_audio = 1; //1 = sin compresion
	escribir(archivo, formato_del_audio, 2);
	
	int cantidad_de_canales = 1; //1 = mono
	escribir(archivo, cantidad_de_canales, 2);
	
	escribir(archivo, sample_rate, 4);
	
	int byte_rate = sample_rate * cantidad_de_canales * bit_depth / 8;
	escribir(archivo, byte_rate, 4);
	
	int block_align = cantidad_de_canales * bit_depth / 8;
	escribir(archivo, block_align, 2);
	
	escribir(archivo, bit_depth, 2);
}


void EndianSwap32(char c[]){
	
	unsigned char tmp;
    tmp  = c[0];
    c[0] = c[3];
    c[3] = tmp;
    tmp  = c[1];
    c[1] = c[2];
    c[2] = tmp;
}


int tamanio_del_archivo(int duracion, ) {
	
	int tamanio = duracion * bit_depth * sample_rate;
	return tamanio;
}
