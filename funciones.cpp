// funciones del programa

#include "funciones.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>


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

void amplitud_y_altura(float &A, float &D, int bits){
    if (bits == 8){A = 127; D = 128;}
    else if (bits == 16){A = 32767; D = 0;}
    else {A = 65535; D = 0;}
}

// f(x) = A Sen(2*PI*Bx+C)+D
int frec_a_sonido(float A, float B, float &x, float C, float D, int frecuenciaMuestras){ //x seria la x del muestreo anterior
    int valor;
    x = x + (float)1/frecuenciaMuestras; //Funciona asi?
    valor = (int)(A*sin(2*PI*B*x+C)+D);
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
    posicion = linea.find("\t");
    if (eof){
        dato.nota = linea.substr(0,posicion-1);
        auxiliar << linea.substr(posicion+1);
        auxiliar >> dato.duracion;
    }
    return eof;
}

float sonido(nota_y_tiempo dato, float defasaje, float amplitud, float altura, ofstream &archivo_wav, int frec_muestras, int bits){ //esto es medio pseudocodigo
    dato.frecuencia = nota_a_frecuencia(dato.nota);
    float x = 0;
    while(x < (float)dato.duracion/1000){ //esto depende de las unidades de "duracion"
        int valor = frec_a_sonido(amplitud, dato.frecuencia, x, defasaje, altura, frec_muestras);
        wav(valor, archivo_wav, bits);
    } 
    return 2*PI*dato.frecuencia*x+defasaje;            
    
}

int salto_nota(string nota){
	
	if (nota != "H") {
		
		int octava = nota[nota.length()-1] - '0'; //como los numeros en ascii empiezan en 48 (no en 0), asi puedo
		                                        //obtener el numero en enteros correspondiente a la octava en la nota ej '2' - '0' es 50-48 que es 2
		nota.erase(nota.length()-1);
		int salto = 12 * (octava - 4);
		
		if (nota == "B")        salto += 2;
        else if (nota == "A#")  salto += 1;
        else if (nota == "A")   salto += 0;
        else if (nota == "G#") salto += -1;
        else if (nota == "G")  salto += -2;
        else if (nota == "F#") salto += -3;
        else if (nota == "F")  salto += -4;
        else if (nota == "E")  salto += -5;
        else if (nota == "D#") salto += -6;
        else if (nota == "D")  salto += -7;
        else if (nota == "C#") salto += -8;
        else                   salto += -9;
		return salto;
	}
	else return 0;
}

void header_y_formato(int duracion_tot, ofstream &archivo, int bits, int frec_muestras){
    int tamanio_valores = bits*frec_muestras*duracion_tot/1000;
    //header y formato
    archivo << "RIFF";
    little(tamanio_valores+36, 4, archivo);
    archivo << "WAVE";
    archivo << "fmt";
    little(16,4,archivo);
    little(1,2,archivo);
    little(1,2,archivo);
    little(frec_muestras,4,archivo);
    little(frec_muestras*bits/8,4,archivo);
    little(bits,2,archivo);
    //datos
    archivo << "data";
    little(tamanio_valores,4,archivo);
}

void little(int valor, int bytes, ofstream &archivo){
    int mascara = 255; int resultado;
    char valor_a_grabar;
    for (int i = 0; i < bytes; i++){
        resultado = valor & mascara;
        valor_a_grabar = resultado;
        archivo << valor_a_grabar;
        valor = valor >> 8;
    }
}


void wav(int valor, ofstream &archivo, int bits){ //Deberia tomar algun parametro de posicion de la ultima linea del archivo? Devolver algo?
    little(valor, bits/8, archivo);
    }






