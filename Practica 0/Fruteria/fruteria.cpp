/**
  * @file fruteria.cpp
  * @brief Programa para la gestión de tickets de compra usando structs
  * @author MP-DGIM - Grupo A
  *
  */

#include<iostream>
#include<string>

using namespace std;

struct Producto{
    string nombre;
    int peso; // en gramos
    float precio_kg;
};

struct Compra{
    static const int MAX = 10;
    Producto lista[MAX];
};

// Imprime un producto en pantalla
void imprimeProducto(Producto a){
    cout << a.nombre << "\t\t" << a.peso << "\t" << a.precio_kg;
}

// Crea un producto y lo inicializa con los parámetros que recibe
Producto creaProducto(string nombre, int peso, float precio){
	Producto miproducto;

	miproducto.nombre = nombre;
	miproducto.peso = peso;
	miproducto.precio_kg = precio;

return miproducto;
}

// Incrementa el precio por kilo de los productos de una lista en k%
void incrementarPrecios(Compra & c, int k){
    for(int i=0; i<c.MAX; i++){
      c.lista[i].precio_kg += (c.lista[i].precio_kg*k)/100;
    }
}

// Muestra la lista de la compra
void imprimirCompra(const Compra & c){
  for(int i=0; i<c.MAX; i++){
    cout << c.lista[i].nombre << " " << c.lista[i].peso << " " << c.lista[i].precio_kg << endl;
  }
}

// Extrae el precio y el peso totales de una lista de la compra
void obtenerImporteYPeso(const Compra & c, float & precio, int & peso){
  precio = 0;
  peso = 0;

  for(int i=0; i<c.MAX; i++){
    peso += c.lista[i].peso;
    precio += (c.lista[i].peso*c.lista[i].precio_kg)/1000.0;
  }
}

// Muestra la lista de la compra y el importe final desglosado en subtotal, IVA y total
void imprimirTicketCompra(const Compra & c){
  double precio = 0;
  double total, suma;
  const int IVA = 21;

  for(int i=0; i<c.MAX; i++){
    precio += (c.lista[i].peso*c.lista[i].precio_kg)/1000.0;
  }

  suma = (precio*IVA)/100.0;
  total = suma + precio;

  imprimirCompra(c);
  cout << "\nSubtotal: " << precio;
  cout << "\nIVA(21%): " << suma;
  cout << "\nTotal de la compra: " << total;
}


int main(){
    const int TAM = 10;
    Producto actual;
    Compra mi_compra;
    float precio;
    int peso;
    string nombre;

    for(int i = 0; i < TAM; i++){
        cin >> nombre >> peso >> precio;
        mi_compra.lista[i] = creaProducto(nombre, peso, precio);
    }

    // se muestra la lista de productos.
    cout << "\n ******** Prueba de funcion listarCompra ******** \n";
    imprimirCompra(mi_compra);

    // se muestra el importe total de la compra y el peso
    cout << "\n ******** Prueba de funcion obtenerImporteYPeso ******** \n";
    obtenerImporteYPeso(mi_compra, precio, peso);
    cout << "\nEl importe de la compra es: " << precio << ", su compra pesa:"
		 << peso << " Kg. " << endl;

    // se muestra el ticket de la compra.
    cout << "\n ******** Prueba de la funcion mostrarTicketCompra ******** \n";
    imprimirTicketCompra(mi_compra);

    cout << "\n ******** Prueba de la funcion incrementarPrecio ********";
    incrementarPrecios(mi_compra, 10);
    cout << "\n ******** y listarCompra de nuevo   \t\t********\n\n";
    imprimirCompra(mi_compra);

    return(0);
}
