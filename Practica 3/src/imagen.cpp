/**
   @file imagen.h
   @brief Manejo de imágenes digitales en formato PGM blanco y negro
   @author MP-DGIM - Grupo A

**/

#include "byte.h"
#include "pgm.h"
#include "imagen.h"
#include <iostream>
using namespace std;

/**
@brief Una imagen en blanco y negro. Cada píxel es un Byte
*/

bool CompruebaAcceso(int fil, int col, const int MAXPIXELS) {
  return fil >= 0 &&  col >= 0 && fil*col < MAXPIXELS;
}

Imagen::Imagen() {
 nfilas = 0;
 ncolumnas = 0;
 for (int i = 0; i < MAXPIXELS; i++)
  datos[i] = 0;
}

/**
@brief Construye una imagen negra de tamaño @a filas x @a columnas
@param filas 	número de filas de la imagen
@param columnas	número de columnas de la imagen

Construye una imagen de tamaño @a filas x @a columnas y pone todos
sus elementos a 0.
*/
Imagen::Imagen(int filas, int columnas) {
  crear(filas, columnas);
}

/**
@brief Crea una imagen negra de tamaño @a filas x @a columnas
@param filas 	número de filas de la imagen
@param columnas	número de columnas de la imagen

Dimensiona la imagen a tamaño @a filas x @a columnas y pone todos
sus elementos a 0.
*/
void Imagen::crear(int filas, int columnas) {
 if (CompruebaAcceso(filas, columnas, MAXPIXELS)) {
   nfilas = filas;
   ncolumnas = columnas;
   for (int i = 0; i < MAXPIXELS; i++)
    datos[i] = 0;
 }
}


/**
@brief Devuelve el número de filas de las imagen
@return el número de filas de la imagen
*/
int Imagen::filas() const {
  return nfilas;
}


/**
@brief Devuelve el número de columnas de las imagen
@return el número de columnas de la imagen
*/
int Imagen::columnas() const {
 return ncolumnas;
}


/**
@brief Asigna el valor @a v a la posición (@a x,@a y) de la imagen
@param y 	fila de la imagen
@param x 	columna de la imagen
@param v 	valor a asignar

Asigna el valor @a v a la posición (@a x,@a y) de la imagen. Dado que la imagen se guarda
como un vector, la posición (@a x,@a y) corresponde a la posición @a y * @c ncolumnas + @a x
del vector.
*/
void Imagen::set(int y, int x, Byte v) {
 if (CompruebaAcceso(y, x, MAXPIXELS))
  datos[y*ncolumnas + x] = v;
}


/**
@brief Devuelve el valor de la posición (@a x,@a y) de la imagen
@param y	 fila de la imagen
@param x	 columna de la imagen
@return el valor de la posición (@a x,@a y) de la imagen

Devuelve el valor de la posición (@a x,@a y) de la imagen. Dado que la imagen se guarda
como un vector, la posición (@a x,@a y) corresponde a la posición @a y * @c ncolumnas + @a x
del vector.
*/
Byte Imagen::get(int y, int x) const {
 return datos[y*ncolumnas + x];
}


/**
@brief Asigna el valor @a v a la posición @a i de la imagen considerada como vector
@param i 	posición de la imagen considerada como vector
@param v 	valor a asignar

Asigna el valor @a v a la posición @a i de la imagen considerada como vector. La posición @a i
corresponde con la posición @c y * @c ncolumnas + @c x de la imagen donde @c y representa la
fila y @c x representa la columna.
*/
void Imagen::setPos(int i, Byte v) {
 if (i >= 0 && i < MAXPIXELS)
   datos[i] = v;
}


/**
@brief Devuelve el valor de la posición @a i de la imagen considerada como vector
@param i 	posición de la imagen considerada como vector

Devuelve el valor de la posición @a i de la imagen considerada como vector. La posición @a i
corresponde con la posición @c y * @c ncolumnas + @c x de la imagen donde @c y representa la
fila y @c x representa la columna.
*/
Byte Imagen::getPos(int i) const {
 return datos[i];
}


/**
@brief Carga una imagen desde un fichero
@param nombreFichero nombre del fichero que contiene la imagen
@retval true 	si ha tenido éxito en la lectura
@retval false 	si se ha producido algún error en la lectura

Lee desde disco los datos de la imagen llamada @a nombreFichero y la guarda en
la memoria. La función debe asegurarse de que la imagen es de un tipo de imagen
conocido y de que su tamaño es menor del tamaño máximo permitido (@c MAXDATOS).
*/
bool Imagen::leerImagen(const char nombreFichero[]) {
  int filas, columnas;
  bool result = false;
  if (infoPGM (nombreFichero, filas, columnas) == IMG_PGM_BINARIO) {
    if (filas*columnas < MAXPIXELS &&
        leerPGMBinario(nombreFichero, datos, filas, columnas)) {
      nfilas = filas;
      ncolumnas = columnas;
      result = true;
    }
  }
  return result;
}


/**
@brief Guarda una imagen desde un fichero
@param nombreFichero nombre del fichero que contiene la imagen
@param esBinario toma el valor @c true si el fichero se escribe en formato binario o @c false en caso contrario.
@retval true 	si ha tenido éxito en la escritura
@retval false 	si se ha producido algún error en la escritura
*/
bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario) const {
 bool result = false;
 if (esBinario) {
   result = escribirPGMBinario(nombreFichero, datos, nfilas, ncolumnas);
 }
 return result;
}

///////////////////////////////////////////////////////////////////////////////////
Imagen Imagen::plano (int k) const {
  Imagen nueva(this->nfilas, this->ncolumnas);
  Byte aux = 0x01 << k;
  int k2 = 7-k, tope = this->nfilas * this->ncolumnas;
  for (int i=0; i<tope; i++)
    nueva.datos[i] = (this->datos[i] & aux) << k2;
  return nueva;
}

bool Imagen::aArteASCII(const char grises[], char arteASCII[], int maxlong) const {
  bool result = false;
  int tope = this->nfilas * (this->ncolumnas + 1);
  if (maxlong >= tope) {
    int cardinal = sizeof(grises), j=0, k=0;
    for (int i=0; i<tope; i++) {
      arteASCII[j] = grises[this->datos[i]*10/255];
      j++;
      k++;
      if (k == this->ncolumnas) {
        arteASCII[j] = '\n';
        j++;
        k = 0;
      }
    }
    result = true;
  }
  return result;
}
///////////////////////////////////////////////////////////////////////////////////
