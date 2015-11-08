#include <iostream>
#include <stdio.h>
#ifndef __PILA__
#define __PILA__

struct Operacion{int arg1, arg2, op;};

int Opera(const int a, const int b, int op);

inline int Resultado(Operacion o){return Opera(o.arg1, o.arg2, o.op);}

std::ostream& operator<<(std::ostream& os, const Operacion& op);


class Pila{
  Operacion pila[6];
  int nelem;
public:
  Pila():nelem(0){}
  inline void push(Operacion op){pila[nelem++]=op;}
  inline void pop(){nelem--;}
  inline void clear(){nelem = 0;}
  inline int  size(){return nelem;}
  inline bool empty(){return !nelem;}

  // Imprime la solución
  void Imprime(int iniciales[6], bool usados[6], int n = -1);
};

#endif
