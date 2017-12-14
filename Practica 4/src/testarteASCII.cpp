/**
   @file testarteASCII.cpp
   @brief lee imagenes/gio.pgm y la convierte en ascii con los caracteres "@%#*+=-:. "
   @author MP-DGIM - Grupo A

**/
#include <iostream>
#include <imagen.h>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(){
	 const int MAX=4500;
	 string nombreImagen, nombreEntrada, nombreSalida, grises;
    char arteASCII[MAX+1]; // 4500 + el \0
		ifstream fentrada;
		ofstream fsalida;
		int nImagenes;
    Imagen imagen;

		// Leemos la imagen
		cout << "Introduzca nombre de la imagen:" << endl;
		cin >> nombreImagen;

    if (!imagen.leerImagen(nombreImagen.c_str())){
	   cerr << "error leyendo "<< nombreImagen << endl;
	   return 1;
    }
		cout << "Imagen " << nombreImagen << " leida correctamente" << endl;

		// Leemos el fichero de grises
		cout << "Introduzca nombre del fichero de entrada:" << endl;
		cin >> nombreEntrada;

		fentrada.open(nombreEntrada.c_str());

		if (!fentrada) {
			cerr << "Error al abrir el fichero de entrada" << endl;
			return 1;
		}

		// Leemos el nombre del fichero de salida y lo creamos
		cout << "Introduzca nombre del fichero de salida:" << endl;
		cin >> nombreSalida;

		fsalida.open(nombreSalida.c_str());

		if (!fentrada) {
			cerr << "Error al abrir el fichero de salida" << endl;
			return 1;
		}

		// Leemos el número de imágenes a representar
		getline(fentrada, grises);
		nImagenes = atoi(grises.c_str());

		// Imprimos las imagenes nImagenes veces para las distintas cadenas de grises
		for (int i = 0; i<nImagenes; i++) {
			getline(fentrada, grises);
			fsalida << "\nLa imagen en arte ASCII(" << i << ") es:\n";
			if(imagen.aArteASCII(grises.c_str(), arteASCII, MAX, grises.size() - 1))
					fsalida << arteASCII << endl;
			else
					fsalida << "La conversión no ha sido posible" << endl;
			fsalida << endl;
		}
}
