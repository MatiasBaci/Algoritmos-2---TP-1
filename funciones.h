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

//void obtener_nota(string nota_y_duracion, string *vector[]);

int distancia_semitonos(string nota);

float nota_a_frecuencia(string nota);

int frec_a_sonido(float amplitud, float freq, float &t, float defasaje, int sample_rate, int bit_depth);

int string_a_int(string cadena);

float sonido(ofstream& archivo_wav, string nota, int duracion, float defasaje, float amplitud, int sample_rate, int bit_depth);

void musica(ifstream& archivo_txt, ofstream& archivo_wav, float amplitud, int sample_rate, int bit_depth);

int leer_int(ifstream& archivo_txt);

void escribir(ofstream& archivo_wav, int valor, int bit_depth);

void escribir_str(ofstream& archivo_wav, string valor);

int string_to_hex(string cadena);

void escribir_chunk_header(ofstream& archivo_wav, int duracion_archivo, int bit_depth, int sample_rate);

void escribir_chunk_formato(ofstream& archivo_wav, int bit_depth, int sample_rate);

void escribir_chunk_data(ifstream& archivo_txt, ofstream& archivo_wav, float amplitud, int sample_rate, int bit_depth, int duracion_archivo);

void EndianSwap32(char c[]);

int tamanio_data(int duracion_archivo, int bit_depth, int sample_rate);
