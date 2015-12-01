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
	return RealAleatorio() < 2.0/nivel;
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
  salida.open("arbol.tree", ios::binary);
  GuardaArboles g(salida, &a);
  g.Guarda();
  salida.close();
  
  AB b;
  ifstream entrada;
  entrada.open("arbol.tree", ios::binary);
  LeeArboles l(entrada, &b);
  l.Lee();
  entrada.close();
  
  if (a == b)
	cout << "Éxito: el árbol de memoria y el árbol leído de disco coinciden\n";
  else
	cout << "Fracaso\n" << "Árbol original:\n" << a << "\n\nÁrbol recreado de disco:\n" << b << "\n\n";

}