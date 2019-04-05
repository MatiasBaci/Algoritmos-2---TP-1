// funciones del programa
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream> // es necesario todo esto?
using namespace std;
const int FRECUENCIA_MUESTRAS = 44100;
const float FREQ_A4 = 440;

// f(x) = A sin(Bx+C) + D
int frec_a_sonido(float A, float B, float &x, float C){ //x seria la x del muestreo anterior
    int valor;
    x = x + 1/FRECUENCIA_MUESTRAS; //Funciona asi?
    valor = (int)(A*sin(B*x+C));
    return valor;
}


int distancia_semitonos(string nota){
	
	if nota != "H" {
		
		int octava = (int) nota.back();
		nota.pop_back();
		int distancia = 12 * (octava - 4);
		
		switch(nota){
				case "G#": distancia += 11; break;
				case "G":  distancia += 10; break;
				case "F#": distancia += 9; break;
				case "F":  distancia += 8; break;
				case "E":  distancia += 7; break;
				case "D#": distancia += 6; break;
				case "D":  distancia += 5; break;
				case "C#": distancia += 4; break;
				case "C":  distancia += 3; break;
				case "B":  distancia += 2; break;
				case "A#": distancia += 1; break;
				case "A":  distancia += 0; break;
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


void leer_archivo(archivo, vector[]){ //aca quiero que lea 2 lineas de archivo y lo guarde en un vector.
    //una linea para la nota y otra la duracion
    string cadena;
    string nota;
    string duracion_str;
    int duracion;
    int separacion;
    
    getline(archivo, cadena);
    separacion = cadena.find(" ");
    nota = cadena.substr(0, separacion-1);
    duracion_str = cadena.substr(separacion+1, 10);
    duracion = (int) duracion_str;
    vector[0] = nota;
    vector[1] = duracion;
}


float sonido(string nota, int duracion, float defasaje, float amplitud) {
    frecuencia = nota_a_frecuencia(nota);
    float x = 0;
    while (x < (float) duracion) { //esto depende de las unidades de "duracion"
        escribir_archivo(frec_a_sonido(amplitud, frecuencia, x, defasaje));
    }
    return defasaje;
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
