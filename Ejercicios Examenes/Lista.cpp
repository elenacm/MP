#include <iostream>
#include <fstream>
#include "Lista.h"

using namespace std;

Lista::Lista()
{
    //ctor
    elementos=0;
    primero=-1;
    nelems=0;
}

Lista::Lista(const Lista &lista){
    this->primero=lista.primero;
    this->nelems=lista.nelems;
    this->elementos=new dato[lista.nelems];
    for(int i=0;i<this->nelems;++i){
        this->elementos[i]=lista.elementos[i];
    }
}

Lista::~Lista() //dtor
{
    if(nelems>0)
        delete[] this->elementos;
}

Lista& Lista::operator=(const Lista &lista){
    if(this!=&lista){
        if(nelems>0)
            delete[] this->elementos;
        this->elementos=new dato[lista.nelems];
        this->primero=lista.primero;
        this->nelems=lista.nelems;
        for(int i=0;i<this->nelems;++i){
            this->elementos[i]=lista.elementos[i];
        }
    }
    return *this;
}


bool Lista::operator==(const Lista &lista) const{
    if(this->nelems!=lista.nelems){
        return false;
    }
    else{
        int sig1=this->primero;
        int sig2=lista.primero;

        while(sig1!=-1){ // se supone que -1 marca el final de la lista
                        // También podría usarse for(int i=0;i<this->nelems;++i)
            if(this->elementos[sig1].elem!=lista.elementos[sig2].elem){
                return false;
            }
            else{
                sig1=this->elementos[sig1].siguiente;
                sig2=lista.elementos[sig2].siguiente;
            }
        }
    }
    return true;
}

bool Lista::guardar(const char *fichero) const{
    ofstream f(fichero,ios::out|ios::binary);
    if(f){
        f.write(reinterpret_cast<const char*>(&(this->nelems)),sizeof(int));
        f.write(reinterpret_cast<const char*>(&(this->primero)),sizeof(int));
        f.write(reinterpret_cast<const char*>(this->elementos),sizeof(dato)*this->nelems);
        f.close();
        return true;
    }
    else{
        cerr<<"Imposible crear el fichero "<<fichero<<endl;
    }
    return false;
}

bool Lista::cargar(const char *fichero){
    ifstream f(fichero,ios::in|ios::binary);
    if(f){

        if(this->nelems>0)
            delete[] this->elementos;
        f.read(reinterpret_cast<char*>(&(this->nelems)),sizeof(int));
        f.read(reinterpret_cast<char*>(&(this->primero)),sizeof(int));

        this->elementos=new dato[this->nelems];

        f.read(reinterpret_cast<char*>(this->elementos),sizeof(dato)*this->nelems);
        f.close();
        return true;
    }
    else{
        cerr<<"Imposible abrir el fichero "<<fichero<<endl;
    }
    return false;
}

int Lista::indexElemento(int pos) const{
    if(pos<0 || pos>=this->nelems){
        return -1;
    }
    else{
        int index=this->primero;
        for(int i=0;i<pos;++i){
            index=this->elementos[index].siguiente;
        }
        return index;
    }
}
void Lista::insertar(float valor,int posicion){
    dato *p=new dato[this->nelems+1]; // Ampliamos espacio
    for(int i=0;i<this->nelems;++i){ // Copiamos elementos antiguos
        p[i]=this->elementos[i];
    }

    if(this->nelems>0) // Liberamos espacio antiguo
        delete[] this->elementos;
    this->elementos=p;

    this->elementos[this->nelems].elem=valor; // Insertamos valor

    if(this->nelems==0){ // Si lista estaba vacía
        this->elementos[0].siguiente=-1;
        this->primero=0;
    }
    else{
        if(posicion<=0){ // Si insertamos al principio de la lista
            this->elementos[this->nelems].siguiente=this->primero;
            this->primero=this->nelems;
        }
        else{ // Si insertamos en una posición más allá del principio
            posicion=posicion<this->nelems?posicion:this->nelems;
            int anterior=indexElemento(posicion-1);
            int sig=this->elementos[anterior].siguiente;
            this->elementos[anterior].siguiente=this->nelems;
            this->elementos[this->nelems].siguiente=sig;
        }
    }
    this->nelems++;
}

void Lista::print(ostream &flujo) const{
    flujo<<"Número elementos: "<<this->getNelems()<<" Primero: "<<this->getPrimero()<<endl;
    for(int i=0;i<this->getNelems();++i){
        flujo<<this->getElemento(i).elem<<", "<<this->getElemento(i).siguiente<<endl;
    }
    cout<<endl;
}

ostream& operator<<(ostream &flujo, const Lista &lista){
    int sig=lista.getPrimero();
    for(int i=0;i<lista.getNelems();++i){
        flujo<<lista.getElemento(sig).elem<<" ";
        sig=lista.getElemento(sig).siguiente;
    }
    cout<<endl;
}



