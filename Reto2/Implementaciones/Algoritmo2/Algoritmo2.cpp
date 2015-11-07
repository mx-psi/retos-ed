#include <iostream>
#include <ctime>
#include <cmath>
#include "arbol.h"

using namespace std;
void Cifras(int solucion, int disponibles[6]){
  nodo *traza=new nodo[6];
  int m=0;
  int *buffer;
  bool encontrado=false;
  int mejor_aprox=disponibles[0];

  clock_t tini;
  clock_t tfin;

  tini=clock();
  encontrado=Recorrer(disponibles,6,solucion,traza,m,encontrado,mejor_aprox);
  tfin=clock();

  if(encontrado){cout <<"exito "<< endl;}
  else
  {
    cout << "fracaso "<<endl;
    cout << "mejor aproximaxión: "<<mejor_aprox<< endl;
  }


  if(encontrado)
  {Preetyprint(disponibles,6,traza,m);}

  cout << "tiempo de ejecución: " << (tfin-tini)/(double)CLOCKS_PER_SEC << " segundos" <<endl;
}
