#include <iostream>
#include <cassert>

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
  inline void push(Operacion o){pila[nelem++]=o;}
  inline void pop(){nelem--;}
  inline int size(){return nelem;}

  // Pop devolviendo el valor
  inline Operacion pops(){return pila[--nelem];}
  inline bool empty(){return !nelem;}

  // Imprime la solución
  void Imprime(int iniciales[6], bool usados[6], int n);
};

#endif
