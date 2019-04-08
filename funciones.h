//declaracion de las funciones del programa
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>
using namespace std;
const float FREQ_A4 = 440;
const int MASCARA = 255;

int leer_duracion(ifstream& archivo_txt);
int string_a_int(string cadena);
void escribir_chunk_header(ofstream& archivo_wav, int duracion_archivo, int bit_depth, int sample_rate);
int tamanio_data(int duracion_archivo, int bit_depth, int sample_rate);
void escribir(ofstream& archivo_wav, int valor, int bit_depth);
void escribir_chunk_formato(ofstream& archivo_wav, int bit_depth, int sample_rate);
void escribir_chunk_data(ifstream& archivo_txt, ofstream& archivo_wav, float amplitud, int sample_rate, int bit_depth, int duracion_archivo);
void musica(ifstream& archivo_txt, ofstream& archivo_wav, float amplitud, int sample_rate, int bit_depth);
float sonido(ofstream& archivo_wav, string nota, int duracion, float defasaje, float amplitud, int sample_rate, int bit_depth);
float nota_a_frecuencia(string nota);
int distancia_semitonos(string nota);
int frec_a_sonido(float amplitud, float freq, float &t, float defasaje, int sample_rate, int bit_depth);

