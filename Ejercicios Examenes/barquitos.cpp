#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>

#include "barquitos.h"

using namespace std;

void Barquitos::reservar(int nfil, int ncol){
  nfilas=nfil;
  ncolumnas=ncol;
  datos=new int*[nfilas];
  datos[0]=new int[nfilas*ncolumnas];
  for(int i=1;i<nfilas;i++){
    datos[i]=datos[i-1]+ncolumnas;
  }
}

void Barquitos::inicializar(){
  for(int i=0;i<nfilas;i++){
    for(int j=0;j<ncolumnas;j++){
      datos[i][j]=9;
    }
  }
}

void Barquitos::copiar(const Barquitos &otroTablero){
  for(int i=0;i<nfilas;i++){
    for(int j=0;j<ncolumnas;j++){
      datos[i][j]=otroTablero.datos[i][j];
    }
  }  
}

void Barquitos::destruir(){
  delete[] datos[0];
  delete[] datos;
  datos=0;
}

Barquitos::Barquitos(int nfil, int ncol){ // apartado 2.a
  reservar(nfil,ncol);
  inicializar();
}

Barquitos::~Barquitos(){ // apartado 2.a
  destruir();
}


Barquitos::Barquitos(const Barquitos &otroTablero){ // apartado 2.b
  reservar(otroTablero.nfilas,otroTablero.ncolumnas);
  copiar(otroTablero);
}

Barquitos& Barquitos::operator=(const Barquitos &otroTablero){ // apartado 2.b
  if(this!=&otroTablero){
    destruir();
    reservar(otroTablero.nfilas,otroTablero.ncolumnas);
    copiar(otroTablero);      
  }
  return *this;
}

bool Barquitos::sePuedePoner(const Posicion &barco) const{ // apartado 2.c

  if(barco.tam>0 && barco.tam<9 &&// si tamaño es correcto
    (barco.fila-'A')>=0 &&  barco.columna-1>=0) // si principio del barco esta dentro del tablero
  { 
    if((barco.direccion=='H' && barco.columna+barco.tam-1<ncolumnas)){ // si final del barco esta dentro del tablero
      for(int i=barco.fila-'A'-1;i<=barco.fila-'A'+1 ;i++){
	for(int j=barco.columna-1-1;j<=barco.columna+barco.tam -1 +1 ;j++){
	  if(i>=0 && i<nfilas && j>=0 && j<ncolumnas){ // si posicion a comprobar esta dentro del tablero
	    if(datos[i][j]!=9) // si no es AGUA
	      return false;
	  }
	}
      }
    }
    else if(barco.direccion=='V' && barco.fila-'A'+barco.tam<nfilas){// si final del barco esta dentro del tablero
      for(int i=barco.fila-'A'-1;i<=barco.fila-'A'+barco.tam+1  ;i++){
	for(int j=barco.columna-1-1;j<=barco.columna-1 + 1;j++){
	  if(i>=0 && i<nfilas && j>=0 && j<ncolumnas){ // si posicion a comprobar esta dentro del tablero
	    if(datos[i][j]!=9) // si no es AGUA
	      return false;
	  }
	}
      }
    }
    else
      return false;
  }
  return true;
}

bool Barquitos::insertar(int tam){ // apartado 2.d
  Posicion posicion;
  int direccion;
  bool colocado=false;
  
  posicion.tam=tam;
  while(!colocado){ // mientras no encuentre posicion correcta
    direccion=Aleatorio(1,2);
    if(direccion==1)
      posicion.direccion='H';
    else
      posicion.direccion='V';
    posicion.fila='A'+Aleatorio(0,nfilas-1);
    posicion.columna=Aleatorio(1,ncolumnas);
    if(sePuedePoner(posicion)){
      colocado=true;
      if(posicion.direccion=='H'){ // Barco horizontal
	for(int i=0;i<posicion.tam;i++){ //Poner barco horizontal en tablero
	  datos[posicion.fila-'A'][posicion.columna-1+i]=posicion.tam;
	}
      }
      else{ // Barco vertical
	for(int i=0;i<posicion.tam;i++){ //Poner barco vertical en tablero	  
	  datos[posicion.fila-'A'+i][posicion.columna-1]=posicion.tam;
	}
      }
    }
  }
  return colocado;
}

bool Barquitos::leer(const char nombre[]){ // Apartado 3.a
  char cadena[100];
  ifstream fin(nombre,ios::in|ios::binary);
  
  if(fin){
    fin.getline(cadena,100); //fin>>cadena;
    if(strcmp(cadena,"MP-BARQ-V1.0")==0){
      destruir();
      fin>>nfilas;
      fin>>ncolumnas;
      fin.get();
      reservar(nfilas,ncolumnas);
      fin.read(reinterpret_cast<char*>(datos[0]),sizeof(int)*nfilas*ncolumnas);
    }
    else
      return false;
  }
  else{
    cerr<<"Imposible leer fichero " << nombre<<endl;
    return false;
  }
  fin.close();
  return true;
}

bool Barquitos::escribir(const char nombre[]) const{ // Apartado 3.b
  ofstream fout(nombre,ios::out|ios::binary);
  if(fout){
    fout<<"MP-BARQ-V1.0"<<endl;
    fout<<this->nfilas<<" "<<this->ncolumnas<<endl;
    fout.write(reinterpret_cast<const char*>(datos[0]),
	       sizeof(int)*this->nfilas*this->ncolumnas);
    fout.close();
  }
  else{
    cerr<<"Imposible crear fichero " << nombre << endl;
    return false;
  }
  return true;
}

std::ostream& operator<<(std::ostream &flujo,const Barquitos &barquitos){
  flujo<<" ";
  for(int j=0;j<barquitos.ncolumnas;j++){ 
    flujo << setw(3) << j+1;
  }
  flujo<<endl;
  
  for(int i=0;i<barquitos.nfilas;i++){
    flujo <<  (char)('A'+i);
    for(int j=0;j<barquitos.ncolumnas;j++){
      flujo << setw(3) << barquitos.datos[i][j];
    }
    flujo<<endl;
  }
  return flujo;
}
  

int Aleatorio(int min, int max){
  return (int) (1.0*(max-min+1)*rand()/(RAND_MAX+1.0)) + min;
}