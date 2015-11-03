#include <iostream>
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
std::ostream& operator<<(std::ostream& os, const Operacion& op){
  os << op.arg2 << repr[op.op] << op.arg1 << "\t= " << Opera(op.arg1, op.arg2, op.op);
  return os;
}

void Pila::Imprime(int iniciales[6], bool usados[6], int n){
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

  std::cout << pila[n] << std::endl;
}
