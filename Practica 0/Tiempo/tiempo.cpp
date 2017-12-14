/**
  * @file tiempo.cpp
  * @brief Utilidades para la gestión de datos temporales usando structs
  * @author MP-DGIM - Grupo A
  *
  */

#include <iostream>
using namespace std;

struct Tiempo{
  int horas, minutos, segundos;
};

int convertirASegundos(Tiempo t){
int segundos_finales = 0;

	segundos_finales = segundos_finales + t.minutos*60 +
			   t.horas*3600 + t.segundos;

return segundos_finales;
}

Tiempo convertirATiempo(int segundos){
Tiempo mitiempo;
	mitiempo.segundos = segundos%60;
	segundos /= 60;
	mitiempo.minutos = segundos%60;
	mitiempo.horas = segundos/60;

return mitiempo;
}

void repararTiempo(Tiempo& t){
int sobra_s = 0;
int sobra_m = 0;
	if(t.segundos < 0 || t.segundos > 59){
		sobra_s = t.segundos/60;
		t.segundos = t.segundos%60;
	}
	t.minutos += sobra_s;
	if(t.minutos < 0 || t.minutos > 59){
		sobra_m = t.minutos/60;
		t.minutos = t.minutos%60;
	}
	t.horas += sobra_m;
}

bool esPosterior(Tiempo t1, Tiempo t2){
bool mayor = false;
int segundos_1, segundos_2;

  segundos_1 = convertirASegundos(t1);
  segundos_2 = convertirASegundos(t2);

  if(segundos_1 < segundos_2)
    mayor = true;
  
return mayor;
}

Tiempo incrementarTiempo(Tiempo t, int s){
Tiempo mitiempo;
	t.segundos += s;
	repararTiempo(t);
	mitiempo = t;
return mitiempo;
}

void imprimeTiempo(Tiempo t)  {
	cout << "[" << t.horas << "h :" << t.minutos << "m :" << t.segundos << "s]" << endl;
}


int main() {
	Tiempo t_inicial={10, 30, 45}, t;
	int aux;

	cout << "Tiempo inicial: ";
	imprimeTiempo(t_inicial);

	cout << "Introduce HH MM SS" << endl;
	cin >> t.horas >> t.minutos >> t.segundos;
	aux = convertirASegundos(t);
	imprimeTiempo(t);
	cout << "Equivalente a " << aux << " segundos" << endl;

	Tiempo taux = convertirATiempo(aux);
	cout << "A la inversa es ";
	imprimeTiempo(taux);

	repararTiempo(t);
	cout << "Reparado es ";
	imprimeTiempo(t);

	if (esPosterior(t_inicial, t))
		cout << "El tiempo inicial es más pequeño" << endl;
	else
		cout << "El tiempo inicial es más grande" << endl;

	taux = incrementarTiempo(t,100);
	cout << "El tiempo inicial más 100 segundos es ";
	imprimeTiempo(taux);

	return 0;
}
