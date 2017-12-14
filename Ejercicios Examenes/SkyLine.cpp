#include <iostream>
#include <fstream>
#include "SkyLine.h"

using namespace std;


// Ejercicio 1
int mezclarUnico(const double array1[], int n1, const double array2[], int n2, double resultado[]){
    int pos1,pos2,posRes;
    
    pos1=pos2=posRes=0;
    while(pos1<n1 && pos2<n2){
        if(array1[pos1]<array2[pos2]){
            resultado[posRes]=array1[pos1];
            pos1++;
        }
        else if(array1[pos1]>array2[pos2]){
            resultado[posRes]=array2[pos2];
            pos2++;
        }
        else{ // iguales
            resultado[posRes]=array1[pos1];
            pos1++;
            pos2++;
        }
        posRes++;
    }
    while(pos1<n1){ // Si quedan datos en array1
        resultado[posRes]=array1[pos1];
        pos1++;
        posRes++;
    }
    while(pos2<n2){ // Si quedan datos en array2
        resultado[posRes]=array2[pos2];
        pos2++;
        posRes++;
    }
    return posRes;
}

// Ejercicio 2.1
SkyLine::SkyLine(){
    nElementos=0;
    abcisas=0;
    alturas=0;
}


// Ejercicio 2.1
SkyLine::~SkyLine(){
    liberarMemoria();
}

void SkyLine::liberarMemoria(){ 
    if (nElementos > 0) {
        delete[] abcisas;
        delete[] alturas;

        abcisas = alturas = 0;
        nElementos = 0;
    }
}

// Ejercicio 2.2
SkyLine::SkyLine(double abcisa1, double abcisa2, double altura){
    reservarMemoria(2);
    abcisas[0]=abcisa1;
    abcisas[1]=abcisa2;
    alturas[0]=altura;
    alturas[1]=0;
}

// Ejercicio 2.3
SkyLine::SkyLine(const SkyLine& otro){
    if(otro.nElementos>0){
        reservarMemoria(otro.nElementos);
    }
    copiar(otro);
}

void SkyLine::reservarMemoria(int n){ 
    nElementos=n;
    abcisas=new double[n];
    alturas=new double[n];
}


// Ejercicio 2.3
SkyLine& SkyLine::operator=(const SkyLine& otro){
    if(this != &otro){
        liberarMemoria();
        reservarMemoria(otro.nElementos);
        copiar(otro);
    }
    return *this;
}

void SkyLine::copiar(const SkyLine& otro){
    //nElementos=otro.nElementos;
    for(int i=0; i<otro.nElementos; i++){
        abcisas[i]=otro.abcisas[i];
        alturas[i]=otro.alturas[i];
    }    
}

// Ejercicio 3
double SkyLine::altura(double abcisa) const{
    int i=0;
    while(i<nElementos && abcisa>=abcisas[i]){ 
        i++;
    }
    if(i>0) // Si abcisa está después del primer punto de abcisa de este SkyLine
        return alturas[i-1];
    else    // Si abcisa está antes del primer punto de abcisa de este SkyLine
        return 0.0;
}

// Ejercicio 4.1
SkyLine SkyLine::operator+(const SkyLine& otro) const{
    SkyLine suma;
    double* arrayAux=new double[nElementos+otro.nElementos];
    
    int n=mezclarUnico(abcisas, nElementos, otro.abcisas, otro.nElementos, arrayAux);
    suma.reservarMemoria(n);
    for(int i=0; i<n; i++){
        suma.abcisas[i]=arrayAux[i];
        suma.alturas[i]=max(altura(arrayAux[i]), otro.altura(arrayAux[i]));
    }
    
    delete[] arrayAux;
    return suma;
}

double max(double a, double b){
    return (a<b)?b:a;
}
    
// Ejercicio 4.2
std::ostream& operator<<(std::ostream& flujo, const SkyLine& skyline){
    flujo<<skyline.nElementos<<endl;
    
    for(int i=0;i<skyline.nElementos;i++){
        flujo<<skyline.abcisas[i]<<" "<<skyline.alturas[i]<<endl;
    }
    return flujo;
}

// Ejercicio 4.3
std::istream& operator>>(std::istream& flujo, SkyLine& skyline){
    int n;
    skyline.liberarMemoria();
    
    flujo>>n;
    skyline.reservarMemoria(n);
    for(int i=0; i<n; i++){
        flujo >> skyline.abcisas[i] >> skyline.alturas[i];
    }
    
    return flujo;
}

// Ejercicio 5.1
bool cargar(const char* nombreFichero, SkyLine& skyline){  
    ifstream flujo(nombreFichero);
    if(flujo){
        string cadena;
        flujo >> cadena;
        if(cadena == "MP-SKYLINE-1-0") {
            flujo >> skyline;
            return true;
        }
    }
    return false;
}

// Ejercicio 5.2
bool salvar(const char* nombreFichero, const SkyLine& skyline){  
    ofstream flujo(nombreFichero);
    if(flujo){
        flujo << "MP-SKYLINE-1-0" << endl;
        flujo << skyline;
        return true;
    }
    return false;
}
