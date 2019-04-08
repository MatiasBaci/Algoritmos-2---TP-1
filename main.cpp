#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include "funciones.h"
using namespace std;


int main(int argc, char* argv[]) {
    validacion(argc,argv); //valida los parametros ingresados por consola
    const char * path_partitura = argv[1];
    const char * path_cancion = argv[2];
    stringstream aux; int bits; int frec_muestras;
    aux << argv[3]; aux >> bits;aux.clear(); aux.str("");
    aux << argv[4]; aux >> frec_muestras;aux.clear(); aux.str("");
    ifstream partitura; partitura.open(path_partitura);
    ofstream cancion; cancion.open(path_cancion);
        
    string linea; getline(partitura, linea); //la primer linea es diferente
    aux << linea;    
    int duracion; aux >> duracion;
    
    float amplitud, defasaje, altura;
    amplitud_y_altura(amplitud, altura, bits);
    defasaje = 0;
    
    nota_y_tiempo dato;
    
    header_y_formato(duracion, cancion, bits, frec_muestras);
    while (leer_archivo(partitura, dato)){
        dato.frecuencia = nota_a_frecuencia(dato.nota);
        defasaje = sonido(dato, defasaje, amplitud, altura, cancion, frec_muestras, bits);
        defasaje = fmod(defasaje, 2*PI);
    }


    partitura.close();
    cancion.close();
    return 0;
}

