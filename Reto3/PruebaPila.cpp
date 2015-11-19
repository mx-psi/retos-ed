#include <iostream>
#include "Pila.h"
using namespace std;

int
main ()
{
  Pila<int> p;
  cout << "Test (Pila vacía al iniciar): ";
  if(!p.vacia())
    cout << "La pila no está vacía al iniciarse con el constructor por defecto" << endl;
  else
    cout << "Correcto" << endl;


  cout << "Test (Inserción de elementos): ";
  bool test1 = true;
  for (int i = 0; i < 10; i++){
    p.poner(i);

    if(p.tope() != i){
      cout << "El elemento en el tope no coincide con el puesto" << endl;
      cout << "\tElemento: " << i << "\tTope: " << p.tope() << endl;
      test1 = false;
      break;
    }

    if(p.elementos() != i+1){
      cout << "La pila no tiene " << i+1 << " elementos" << endl;
      cout << "\tNúmero de elementos: " << p.elementos() << endl;
      test1 = false;
      break;
    }
  }
  if(test1)
    cout << "Correcto" << endl;

  cout << "Test (Equivalencia entre vacía y 0 elementos): ";
  while(!p.vacia())
    p.quitar();
    
  if(p.elementos() != 0){
    cout << "La pila no tiene 0 elementos después de vaciarla" << endl;
    cout << "\tTope: " << p.tope() << endl;
  }
  else
    cout << "Correcto" << endl;

  cout << "Test (Poner y quitar un elemento): ";
  p.poner(1);
  int t = p.tope();
  p.poner(2);
  p.quitar();

  if(t != p.tope()){
    cout << "El tope no coincide al quitar y poner un elemento" << endl;
    cout << "\tTope esperado: " << t << "\tTope obtenido: " << p.tope() << endl;
  }
  else
    cout << "Correcto" << endl;

}
