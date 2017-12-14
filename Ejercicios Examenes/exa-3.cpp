// greep Busca palabras en lí­neas de ficheros
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void busca(ifstream & fi, char * nom_fich, char * cad);

int main(int argc, char **argv){
  if (argc<3){
    cout << "Error en el nÃºmero de parÃ¡metros \n";
    exit (1);
  }
  else{
    char cad[30];
    strcpy(cad, argv[1]);
    for (int i=2; i <argc; i++){
      ifstream fi(argv[i]);
      busca(fi, argv[i], cad);
      fi.close();
    }
  }
  return 0;
}


void busca(ifstream & fi, char * nom_fich, char * cad){
  int lin=1;
  char linea[500];
  fi.getline(linea, 500);
  while(!fi.eof()){
    if(strstr(linea, cad))
      cout << nom_fich << " (linea " << lin << "): " << linea << endl; 
    lin++;
    fi.getline(linea, 50);
  }
  return;
}
