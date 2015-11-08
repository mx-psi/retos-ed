#include "pila.h"

int Opera(const int a, const int b, int op){
  if(op == 0) return b+a;
  if(op == 1) return b-a;
  if(op == 2) return b*a;
  if(op == 3) return (b%a)?0:b/a;
  return 0;
}

// Representación de operaciones
char repr[4] = {'+', '-', '*', '/'};

// Algoritmo de impresión
void Pila::Imprime(int iniciales[6], bool usados[6], int n){
  if(n == -1) n = size() - 1;

  // Si está en los iniciales y no ha sido usado no hace nada
  for (int i = 0; i < 6; i++)
    if(Resultado(pila[n]) == iniciales[i] && !usados[i]){
      usados[i] = true;
      return;
    }

  for(int i = n-1; i >= 0; i--)
    if(Resultado(pila[i]) == pila[n].arg1){
      Imprime(iniciales, usados, i);
      break;
    }

  for(int i = n-1; i >= 0; i--)
    if(Resultado(pila[i]) == pila[n].arg2){
      Imprime(iniciales, usados, i);
      break;
    }

    printf("%-4d %c %-4d = %-4d\n",
    pila[n].arg2, repr[pila[n].op], pila[n].arg1, Resultado(pila[n]));
}
