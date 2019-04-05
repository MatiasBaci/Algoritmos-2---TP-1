// funciones del programa
#include <iostream>
#include <string>
#include <cmath>
#include <fstream> // es necesario todo esto?
using namespace std;
const int FRECUENCIA_MUESTRAS = 44100;

// f(x) = A Sen(Bx+C)+D
int frec_a_sonido(float A, float B, float &x, float C){ //x seria la x del muestreo anterior
    int valor;
    x = x + 1/FRECUENCIA_MUESTRAS; //Funciona asi?
    valor = (int)(A*sin(B*x+C));
    return valor;
}

float nota_a_frecuencia(string nota){
    //hacer que traduzca notas en ASPN a frecuencias en Hz
}

void leer_archivo(){ //aca quiero que lea 2 lineas de archivo y lo guarde en un vector.
                    // una linea para la nota y otra la duracion
}

void sonido(string nota, int duracion, float defasaje, float amplitud){ //esto es medio pseudocodigo
    frecuencia = nota_a_frecuencia(nota);
    float x = 0; 
    while(x < (float)duracion){ //esto depende de las unidades de "duracion"
        escribir_archivo(frec_a_sonido(amplitud, frecuencia, x, defasaje));
        
                
    }
}

int distancia_semitonos(string nota){
	
	if nota != "H" {
		
		int octava = nota.back();
		nota.pop_back();
		int distancia = 12 * (octava - 4);
		
		switch(nota){
				case "H":  distancia = 0; break;
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


void escribir_archivo(int valor){ //Deberia tomar algun parametro de posicion de la ultima linea del archivo? Devolver algo?
    
}






