/**
   @file circulomedio.cpp
   @brief Calcula círculo con centro en medio de dos círculos y radio la mitad de la distancia
   @author MP-DGIM - Grupo A
   @warning Módulo no definitivo (creado para ser modificado)

**/

#include <iostream>
#include <cmath> // sqrt, M_PI
using namespace std;

/// Clase Punto
class Punto {
private:
    double x; ///< coordenada x del punto
    double y; ///< coordenada y del punto};
public:
    Punto(){x=0;y=0;} ///< constructor. Pone a 0 las dos coordenadas
    Punto(double x, double y){this->x=x;this->y=y;}///< constructor. Inicializa un punto con dos valores x y
    double getX() const {return x;} ///< Devuelve la coordenada x del punto
    double getY() const {return y;} ///< Devuelve la coordenada y del punto
    void setX(double nuevoX); ///< Asigna el valor nuevoX a la coordenada x del punto
    void setY(double nuevoY); ///< Asigna el valor nuevoY a la coordenada y del punto
    void escribir() const; ///<  Escribe un punto en formato (x,y)
    void leer(); ///< // Lee un punto en el formato (x,y)
};

void Punto::setX(double nuevoX){
  x = nuevoX;
}

void Punto::setY(double nuevoY){
  y = nuevoY;
}

void Punto::escribir() const{
    cout << "(" << x << "," << y << ")" << endl;
}

void Punto::leer(){
    // Formato de lectura del punto: (x,y)
    char car;
    cin >> car >> x >> car >> y >> car;
}

/// Clase Punto
/// Funciones auxiliares (no son métodos de la clase)
/**
@brief Calcula la distancia entre dos puntos
@param p1 primer punto
@param p2 segundo punto
@return la distancia entre el punto @a p1 y el punto @a p2
*/
double distancia(Punto p1, Punto p2){
double d = 0;

    d = sqrt(pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2));

return d;
}

/**
@brief Calcula el punto que está entre dos puntos dados con distancia mínima a ambos
@param p1 primer punto
@param p2 segundo punto
@return un punto entre el punto @a p1 y el punto @a p2 con distancia mínima a ambos
*/
Punto puntoMedio(Punto p1, Punto p2){
    Punto pMedio;
    pMedio.setX((p1.getX()+p2.getX())/2.0);
    pMedio.setY((p1.getY()+p2.getY())/2.0);
    return pMedio;
}

/// Clase Círculo
class Circulo {
private:
    Punto centro; ///< Centro del círculo
    double radio; ///< radio del círculo
public:
    Circulo(); ///< Constructor: Pone a 0 el punto y el radio
    Circulo(Punto centro, double radio); ///< Constructor: Inicializa el círculo con un centro y un radio
    void set(Punto centro, double radio); ///< Asigna el centro y el radio a un circulo
    Punto getCentro() const; ///< Devuelve el centro de un circulo
    double getRadio() const; ///< Devuelve el radio de un circulo
    void escribir() const; ///< Escribe círculo en formato radio-centro
    void leer(); ///< lee círculo en formato radio-centro
    double area() const; ///< Devuelve el área de un círculo
};

Circulo::Circulo(){
    this->centro.setX(0.0);
    this->centro.setY(0.0);
    this->radio = 0.0;
}

Circulo::Circulo(Punto centro, double radio){
	this->centro = centro;
	this->radio = radio;
	// set(centro,radio);
}

void Circulo::set(Punto centro, double radio){
	this->centro = centro;
	this->radio = radio;
}

Punto Circulo::getCentro() const{
	return centro;
}

double Circulo::getRadio() const{
	return radio;
}

void Circulo::escribir() const{
    cout << radio << "-";
    centro.escribir();
}

void Circulo::leer(){
    // Formato de lectura del círculo: radio-(x,y)
    char car;

    cin >> radio;
    cin >> car; //Leer -
    centro.leer();
}

double Circulo::area() const{
    return M_PI*radio*radio;
}
/// Clase Circulo

/// Funciones auxiliares
/**
@brief Calcula la distancia entre dos circulos
@param c1 primer círculo
@param c2 segundo círculo
@return la distancia entre el círculo @a c1 y el círculo @a c2

La distancia entre dos círculos se define como la distancia entre los centros menos los dos radios.
Nótese que la distancia puede ser negativa si los círculos se intersecan
*/
double distancia (Circulo c1, Circulo c2){
    Punto centro1, centro2;
    double dist;

    centro1=c1.getCentro();
    centro2=c2.getCentro();
    dist=distancia(centro1,centro2)-c1.getRadio()-c2.getRadio();
    return dist;
}

/**
@brief Comprueba si un punto es interior a un círculo
@param p punto a comprobar
@param c circulo
@retval true si el punto @a p es interior al círculo @a c
@retval false en caso contrario
*/
bool interior (Punto p, Circulo c){
bool interior;

    if(distancia(p, c.getCentro()) <= c.getRadio())
      interior = true;
    else
      interior = false;
}

int main()
{
    Circulo c1,c2;

    cout << "Introduzca un circulo en formato radio-(x,y): ";
    c1.leer();
    c1.escribir();
    cout << "Introduzca otro circulo: ";
    c2.leer();
    c2.escribir();

    Circulo res;

    res.set(puntoMedio(c1.getCentro(),c2.getCentro()),
                     distancia(c1.getCentro(),c2.getCentro())/2);
    cout << "La distancia entre los círculos es: " << distancia(c1,c2) << " y el círculo que pasa por los dos centros es: ";
    res.escribir();
    cout << endl;
    return 0;
}

/* Fin: circulomedio.cpp */
