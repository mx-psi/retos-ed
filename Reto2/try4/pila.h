#include <iostream>
#include <cassert>

#ifndef __PILA__
#define __PILA__

struct Operacion{int arg1, arg2, op;};

class Pila{
  Operacion pila[6];
  int nelem;
  friend std::ostream& operator<<(std::ostream& os, const Pila& p);
public:
  Pila():nelem(0){}
  inline void push(Operacion o){pila[nelem++]=o;}
  inline void pop(){nelem--;}
  inline Operacion pops(){return pila[--nelem];}
  inline bool empty(){return !nelem;}
};

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

std::ostream& operator<<(std::ostream& os, const Pila& p){
  for (int i = 0; i < p.nelem; i++)
    os << p.pila[i] << std::endl;
  return os;
}

#endif
