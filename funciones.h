#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream> // es necesario todo esto?

const int A4 = 440;
const float PI = 4*atan(1);

typedef struct{ 
    string nota;
    float frecuencia;
    int duracion;
} nota_y_tiempo;


void validacion(int argc, char* argv[]);

int frec_a_sonido(float A, float B, float &x, float C, float D, int frecuenciaMuestras);

float nota_a_frecuencia(string nota);

int leer_archivo(ifstream &inputFile, nota_y_tiempo &dato);

float sonido(nota_y_tiempo dato, float defasaje, float amplitud, float altura, ofstream &wav, int frec_muestras, int bits);

int salto_nota(string nota);

void escribir_archivo(int valor, ofstream &archivo, int bits, int frec_muestras);




#endif

