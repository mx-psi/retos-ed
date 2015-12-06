#include <iostream>
#include <fstream>
#include "ArbolBinario.h"
#include "ArbolClave.cpp"
#include <ctime>
#include <cstdlib> // rand, srand, RAND_MAX
typedef int Tipo;
typedef ArbolBinario<Tipo> AB;
using namespace std;

// Genera un número real entre 0 y 1
float RealAleatorio() {
  return rand() / (float) RAND_MAX;
}

const int MAXIMO = 100;

// Genera un número entero entre 0 y MAXIMO
int EnteroAleatorio() {
  return rand() % MAXIMO;
}

// Decide si añadir un elemento. La probabilidad se reduce con el nivel
bool NuevoElemento(int nivel) {
  return RealAleatorio() < 10.0/nivel;
}

// Amplía el árbol
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

  // Se guarda el árbol
  ofstream salida;
  salida.open("arbol.tree", ios::out | ios::binary);
  GuardaArboles g(salida, &a);
  g.Guarda();
  salida.close();

  // Se lee el árbol guardado
  AB b;
  ifstream entrada;
  entrada.open("arbol.tree", ios::in | ios::binary);
  LeeArboles l(entrada, &b);
  l.Lee();
  entrada.close();

  // Se comprueba que coinciden
  if (a == b)
    cout << "Éxito: el árbol de memoria y el árbol leído de disco coinciden\n";
  else {
    cout << "Fracaso.\nSe guardará la impresión del árbol original"
         << "en error1.dump y la del leído en error2.dump\n\n";

    ofstream error1, error2;
    error1.open("error1.dump", ios::out);
    error1 << a;
    error1.close();
    error2.open("error2.dump", ios::out);
    error2 << b;
    error2.close();
  }
}
