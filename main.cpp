//		C:\Users\Mati\Documents\GitHub\Algoritmos-2---TP-1\TP2.exe ejemplo.txt carlos.wav 8 44100


//#include <iostream>
#include <string>
//#include <sstream>
//#include <fstream>
#include "funciones.h"
using namespace std;


//int main(int argc, char* argv[]) {
int main() {
	
	//string argv[] = {"ejemplo.txt", "carlos.wav", "8" , "44100"};
	
	//const char* nombre_txt = argv[0];
	//const char* nombre_wav = argv[1];
	string nombre_txt = "ejemplo.txt";
	string nombre_wav = "carlos.wav";
	
//	stringstream ss;	
//	int bit_depth;
//	ss << argv[2];
//	ss >> bit_depth;
	int bit_depth = 8;
//	int sample_rate;
//	ss << argv[3];
//	ss >> sample_rate;
	int sample_rate = 44100;
	
    //ifstream archivo_txt(nombre_txt);
    //ofstream archivo_wav(nombre_wav);
    
    ifstream archivo_txt("ejemplo.txt");
    ofstream archivo_wav("carlos.wav");
    
    int duracion_archivo;
    duracion_archivo = leer_int(archivo_txt);
    
    escribir_chunk_header(archivo_wav, duracion_archivo, bit_depth, sample_rate);
    
    escribir_chunk_formato(archivo_wav, bit_depth, sample_rate);
    
    float amplitud = 127; //fucking que se yo. es igual para todas las notas?
	
	escribir_chunk_data(archivo_txt, archivo_wav, amplitud, sample_rate, bit_depth, duracion_archivo);
	
	archivo_txt.close();
	archivo_wav.close();
	
    return 0;
}

