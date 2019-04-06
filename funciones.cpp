// funciones del programa
#include "funciones.h"

#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream> // es necesario todo esto?

using namespace std;

void validacion(int argc, char* argv[]){
    if (argc < 5)
        cout << "Uso: " << argv[0] << " ARCHIVO_NOTAS CANCION PROFUNDIDAD_BITS FRECUENCIA_MUESTREO" << endl;
    else {
        if (*argv[3] != 8 || *argv[3] != 16 || *argv[3] != 32) //se fija que solo se permitan 8,16 y 32
            cout << "Profundidad de bits invalida. Valores permitidos: 8, 16, 32" << endl;
        if (*argv[4] < 8000)
            cout << "Frecuencia de muestreo invalida. Por favor ingrese un valor superior o igual a 8000" << endl;
    }
}





// f(x) = A Sen(Bx+C)+D
int frec_a_sonido(float A, float B, float &x, float C, float D, int frecuenciaMuestras){ //x seria la x del muestreo anterior
    int valor;
    x = x + (float)1/frecuenciaMuestras; //Funciona asi?
    valor = (int)(A*sin(B*x+C)+D);
    return valor;
}

float nota_a_frecuencia(string nota){
    int s; float frec;
    if (nota != "H"){
        s = salto_nota(nota);
        frec = A4*pow(2,((float)s/12));
    } else frec = 0;
    return frec;
    
}

int leer_archivo(ifstream &inputFile, nota_y_tiempo &dato){
    bool eof; int posicion;
    string linea; stringstream auxiliar; //auxiliar es para convertir string a entero
    eof = getline(inputFile, linea);
    posicion = linea.find(" ");
    if (eof){
        dato.nota = linea.substr(0,posicion-1);
        auxiliar << linea.substr(posicion+1);
        auxiliar >> dato.duracion;
    }
    return eof;
}

float sonido(nota_y_tiempo dato, float defasaje, float amplitud, float altura, ofstream wav, int frec_muestras, int bits){ //esto es medio pseudocodigo
    float frecuencia;
    frecuencia = nota_a_frecuencia(dato.nota);
    float x = 0;
    while(x < (float)dato.duracion){ //esto depende de las unidades de "duracion"
        escribir_archivo(frec_a_sonido(amplitud, frecuencia, x, defasaje, altura, frec_muestras), wav, bits);
    } 
    return frecuencia*x+defasaje;            
    
}

int salto_nota(string nota){
	
	if (nota != "H") {
		
		int octava = nota.back();
		nota.pop_back();
		int salto = 12 * (octava - 4);
		
		switch(nota){
				case "G#": salto += -1; break;
				case "G":  salto += -2; break;
				case "F#": salto += -3; break;
				case "F":  salto += -4; break;
				case "E":  salto += -5; break;
				case "D#": salto += -6; break;
				case "D":  salto += -7; break;
				case "C#": salto += -8; break;
				case "C":  salto += -9; break;
				case "B":  salto += 2; break;
				case "A#": salto += 1; break;
				case "A":  salto += 0; break;
		}
		return salto;
	}
	else return 0;
}


void escribir_archivo(nota_y_tiempo dato, ofstream archivo, int bits, int frec_muestras){ //Deberia tomar algun parametro de posicion de la ultima linea del archivo? Devolver algo?
    
    do {
        
    }
    
}






