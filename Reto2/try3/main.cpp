#include <iostream>
#include <cmath>
#include "arbol.h"

using namespace std;

int main()
{
  int n[6];

  cout << "Introduce los 6 elementos iniciales: ";

  for(int i=0; i<6; i++)
    cin>>n[i];

  nodo *traza=new nodo[6];
  int m=0;
  int *buffer;
  bool encontrado=false;
  int meta;
  int mejor_aprox=n[0];


  cout <<"introduce el elemento a buscar: ";
  cin >>meta;
  clock_t tini;
  clock_t tfin;

  tini=clock();
  encontrado=Recorrer(n,6,meta,traza,m,encontrado,mejor_aprox);
  tfin=clock();

  if(encontrado){cout <<"exito "<< endl;}
  else
  {
    cout << "fracaso "<<endl;
    cout << "mejor aproximaxión: "<<mejor_aprox<< endl;
  }


  if(encontrado)
  {Preetyprint(n,6,traza,m);}

  cout << "tiempo de ejecución: " << (tfin-tini)/(double)CLOCKS_PER_SEC << " segundos" <<endl;

}
