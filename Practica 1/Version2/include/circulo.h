#ifndef _CIRCULO_H
#define _CIRCULO_H

#include "punto.h"

class Circulo {
private:
    Punto centro;
    double radio;
public:
    Circulo();
    Circulo(Punto centro, double radio);
    void set(Punto centro, double radio);
    Punto getCentro() const;
    double getRadio() const;
    void escribir() const;
    void leer();
    double area() const;
};

double distancia (Circulo c1, Circulo c2);
bool interior (Punto p, Circulo c);
#endif
