// funciones del programa
#include <iostream>
#include <string>
#include <cmath>
#include <fstream> // es necesario todo esto?
using namespace std;
const int A4 = 440;

typedef struct{  //deberia ir en .h
    string nota;
    int duracion;
} nota_y_tiempo;


// f(x) = A Sen(Bx+C)+D
int frec_a_sonido(float A, float B, float &x, float C, int frecuenciaMuestras){ //x seria la x del muestreo anterior
    int valor;
    x = x + (float)1/frecuenciaMuestras; //Funciona asi?
    valor = (int)(A*sin(B*x+C));
    return valor;
}

float nota_a_frecuencia(string nota){
    int s; float frec;
    s = salto_nota(nota);
    frec = A4*pow(2,((float)s/12));
    return frec;
    
}

int leer_archivo(ifstream &inputFile, nota_y_tiempo &dato){
    int eof = 0; int posicion;
    string linea;
    eof = getline(inputFile, linea);
    posicion = linea.find(" ");
    if (eof){
        dato.nota = linea.substr(0,posicion-1);
        dato.duracion = linea.substr(posicion+1)
    }
    return eof;
}

float sonido(nota_y_tiempo dato, float defasaje, float amplitud, ofstream wav, int bits){ //esto es medio pseudocodigo
    float frecuencia;
    frecuencia = nota_a_frecuencia(dato.nota);
    float x = 0;
    while(x < (float)dato.duracion){ //esto depende de las unidades de "duracion"
        escribir_archivo(frec_a_sonido(amplitud, frecuencia, x, defasaje), wav, bits);
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
				case "E":  salto +=-5; break;
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


void escribir_archivo(int valor, ofstream archivo, int bits){ //Deberia tomar algun parametro de posicion de la ultima linea del archivo? Devolver algo?
    
}






