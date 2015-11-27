#include <iostream>
#include "Pila.h"
using namespace std;

int main ()
{
  Pila<int> p;
  cout << "Test (Pila vacía al iniciar): ";
  if(!p.vacia())
    cout << "La pila no está vacía al iniciarse con el constructor por defecto" << endl;
  else
    cout << "Correcto" << endl;


  cout << "Test (Inserción de elementos): ";
  bool test1 = true;
  for (int i = 0; test1 && i < 10; i++){
    p.poner(i);

    if(p.tope() != i){
      cout << "El elemento en el tope no coincide con el puesto" << endl;
      cout << "\tElemento: " << i << "\tTope: " << p.tope() << endl;
      test1 = false;
    }

    if(p.elementos() != i+1){
      cout << "La pila no tiene " << i+1 << " elementos" << endl;
      cout << "\tNúmero de elementos: " << p.elementos() << endl;
      test1 = false;
    }
  }
  if(test1)
    cout << "Correcto" << endl;

  cout << "Test (Equivalencia entre vacía y 0 elementos): ";
  while(!p.vacia() && p.elementos() > 0)
    p.quitar();
    
  if(p.elementos() != 0){
    cout << "La pila no tiene 0 elementos después de vaciarla" << endl;
    cout << "\tTope: " << p.tope() << endl;
  }
  else if(!p.vacia())
    cout << "La pila tiene 0 elementos y no está vacía" << endl;
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


  cout << "Test (Copia de pilas): ";
  for (int i = 0; i < 10; i++)
    p.poner(i);

  Pila<int> pa(p);
  Pila<int> pb = p;
  bool test2 = true;
  while(test2 && !p.vacia()) {
    if (p.tope() != pa.tope() || p.tope() != pb.tope()) {
	  cout << "Las pilas copiadas no coinciden" << endl;
	  cout << "\tTope de la original: " << p.tope()
	       << "\tTope de la copia por constructor: " << pa.tope()
		   << "\tTope de la copia por asignación: " << pb.tope()
		   << endl;
	  test2 = false;
	}
	p.quitar();
	pa.quitar();
	pb.quitar();
  }
  if (test2)
	cout << "Correcto" << endl;
}
