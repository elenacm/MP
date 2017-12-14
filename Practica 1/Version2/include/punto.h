#ifndef _PUNTO_H
#define _PUNTO_H


class Punto {
private:
    double x;
    double y;
public:
    Punto(){x=0;y=0;}
    Punto(double x, double y){this->x=x;this->y=y;}
    double getX() const {return x;}
    double getY() const {return y;}
    void setX(double nuevoX);
    void setY(double nuevoY);
    void escribir() const;
    void leer();
};

double distancia(Punto p1, Punto p2);
Punto puntoMedio(Punto p1, Punto p2);
#endif
