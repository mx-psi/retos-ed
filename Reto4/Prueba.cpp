#include <iostream>
#include <fstream>
#include "ArbolBinario.h"
#include "ArbolClave.cpp"
#include <ctime>
typedef int Tipo;
typedef ArbolBinario<Tipo> AB;
using namespace std;

const int MAXIMO = 100;

float RealAleatorio() {
	return rand() / (float) RAND_MAX;
}

int EnteroAleatorio() {
	return rand() % MAXIMO;
}

bool NuevoElemento(int nivel) {
	return RealAleatorio() < 10.0/nivel;
}

void Ampliar(AB &a, AB::Nodo n, int nivel) {
  if (NuevoElemento(nivel)) {
	AB nuevo(EnteroAleatorio());
	a.insertar_izquierda(n, nuevo);
	Ampliar(a, a.izquierda(n), nivel+1);
  }
  if (NuevoElemento(nivel)) {
	AB nuevo(EnteroAleatorio());
	a.insertar_derecha(n, nuevo);
	Ampliar(a, a.derecha(n), nivel+1);
  }
}

int main() {
  // Se construye un árbol aleatorio
  srand(time(0));
  AB a(EnteroAleatorio());
  Ampliar(a, a.raiz(), 1);
  
  cout << "Se ha creado un árbol de " << a.size() << " elementos.\n";

  ofstream salida;
  salida.open("arbol.tree", ios::out | ios::binary);
  GuardaArboles g(salida, &a);
  g.Guarda();
  salida.close();
  
  AB b;
  ifstream entrada;
  entrada.open("arbol.tree", ios::in | ios::binary);
  LeeArboles l(entrada, &b);
  l.Lee();
  entrada.close();
  
  if (a == b)
	cout << "Éxito: el árbol de memoria y el árbol leído de disco coinciden\n";
  else {
	cout << "Fracaso.\nSe guardará la impresión del árbol original"
         << "en error1.dump y la del leído en error2.dump\n\n";

    ofstream error1, error2;
    error1.open("error1.dump", ios::out);
    error1 << a;
    error2.open("error2.dump", ios::out);
    error2 << a;
  }
}