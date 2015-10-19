#include <iostream>
#include <vector>
using namespace std;

char operadores[] = {'+', '-', '*', '/'};   // Se va a indicar la suma con 0, la resta con 1, el producto con 2 y el cociente con 3

inline int Diferencia(int a, int b) {
   return b<a ? a-b : b-a;
}

// Hace a op b. Aprovecha que siempre hay como mucho una resta y una division permitida
inline int Opera(int a, int b, short int op) {
   if (op == 0)   return a+b;
   if (op == 1)   return Diferencia(a, b);
   if (op == 2)   return a*b;
   if (op == 3)   return (a == 0 || b == 0) ? 0 : (a%b == 0 ? a/b : (b%a == 0 ? b/a : 0));
}

struct Nodo {
   int previo1;          // Posiciones de los nodos anteriores
   int previo2;
   short int op;         // Operación con la que se ha llegado a este nodo
   int generacion;       // Puede obtenerse de usados, pero está aquí para acelerar
   unsigned int usados;  // El i-ésimo bit menos significativo indica si el i-ésimo número disponible está usado
   int valor;
};

// Comprueba si un par de nodos proceden de un mismo número inicial
inline bool SeSolapan(unsigned int a, unsigned int b) {
   return a&b;
}

// Añade a un vector de nodos todos los que pueden obtenerse a partir de ellos
bool OtraGeneracion(vector<Nodo> &nodos, int &mas_cercano, int objetivo, int generacion) {
   int size_inicial = nodos.size();
   for (int i = 0; i < size_inicial-1; i++) {
   	unsigned int usados_i = nodos[i].usados;
      for (int j = i+1; j < size_inicial; j++)
         if (!SeSolapan(usados_i, nodos[j].usados) && nodos[i].generacion + nodos[j].generacion == generacion)
            for (short int k = 0; k < 4; k++) {
               int resultado = Opera(nodos[i].valor, nodos[j].valor, k);
               if (resultado != 0 && resultado != nodos[i].valor && resultado != nodos[j].valor) {
                  Nodo nuevo = {i, j, k, generacion, nodos[i].usados | nodos[j].usados, resultado};
                  nodos.push_back(nuevo);
                  int diferencia = Diferencia(nodos[nodos.size()-1].valor, objetivo);
                  if (diferencia < Diferencia(nodos[mas_cercano].valor, objetivo)) {
                     mas_cercano = nodos.size()-1;
                     if (diferencia == 0) return false;
                  }
               }
            }
	}

   return generacion < 6;
}

// Recrea la secuencia de operaciones con las que se ha llegado a un determinado nodo 
void Recrea(vector<Nodo> &vec, Nodo &nodo) {
   if (&nodo != 0 && nodo.generacion > 1) {
      Recrea(vec, vec[nodo.previo1]);
      Recrea(vec, vec[nodo.previo2]);
      short int operador = nodo.op;
      int valor1 = vec[nodo.previo1].valor;
      int valor2 = vec[nodo.previo2].valor;
      if ((operador%2) && valor1 < valor2)
         cout << valor2 << ' ' << operadores[operador] << ' ' << valor1 << " = " << nodo.valor << '\n';
      else
         cout << valor1 << ' ' << operadores[operador] << ' ' << valor2 << " = " << nodo.valor << '\n';
   }
}

// Resuelve un problema y muestra la solución
void Cifras(int solucion, int disponibles[]) {
   vector<Nodo> nodos(6);
   for (int i = 0; i < 6; i++)
      nodos[i] = {0, 0, 0, 1, (1 << i), disponibles[i]};
      
   int mas_cercano = 0;
   for (int g = 1; OtraGeneracion(nodos, mas_cercano, solucion, g); g++);
   
   Recrea(nodos, nodos[mas_cercano]);
}

int main() {
   int solucion = 767;
   int disponibles[] = {2,6,7,9,50,75};
   
   Cifras(solucion, disponibles);
}
