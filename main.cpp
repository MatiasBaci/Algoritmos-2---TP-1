#include <iostream>
#include <string>
#include <sstream>
using namespace std;


int main(int argc, char* argv[]) {
	
	string archivo_txt = argv[0];
	
	string nombre_wav = argv[1];
	
	stringstream ss;	
	int bit_depth;
	ss << argv[2];
	ss >> bit_depth;
	
	int sample_rate;
	ss << = argv[3];
	ss >> sample_rate;
	
    ifstream lectura(archivo_txt);
    ofstream escritura(nombre_wav);
    
    int duracion_archivo;
    duracion_archivo = leer_int(archivo_txt);
    
    int tamanio_archivo;
    tamanio_archivo = escribir_header(archivo_txt, duracion_archivo, bit_depth, sample_rate);
    
    escribir_formato(archivo, bit_depth, sample_rate);
    
    float amplitud = 128; //fucking que se yo. es igual para todas las notas?
	
	escribir_chunk_data(amplitud, sample_rate, bit_depth, archivo, tamanio_archivo);
	    
    return 0;
}

