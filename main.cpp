#include <string>
#include "funciones.h"
using namespace std;

int main(int argc, char* argv[]) {

	const char* nombre_txt = argv[1];
	const char* nombre_wav = argv[2];
	
	stringstream ss;
	
	int bit_depth;
	ss << argv[3];
	ss >> bit_depth;
	ss.clear(); ss.str("");
	
	int sample_rate;
	ss << argv[4];
	ss >> sample_rate;
	ss.clear(); ss.str("");
	
    ifstream archivo_txt(nombre_txt);
    ofstream archivo_wav(nombre_wav);
    
    int duracion_archivo;
    duracion_archivo = leer_duracion(archivo_txt);
    float amplitud;
    amplitud = pow ( 2 , bit_depth - 1 );
	
    escribir_chunk_header(archivo_wav, duracion_archivo, bit_depth, sample_rate);
    escribir_chunk_formato(archivo_wav, bit_depth, sample_rate);
	escribir_chunk_data(archivo_txt, archivo_wav, amplitud, sample_rate, bit_depth, duracion_archivo);
	
	archivo_txt.close();
	archivo_wav.close();
	
    return 0;
}

