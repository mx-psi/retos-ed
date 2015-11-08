#include <iostream>
#include <algorithm> //sort
#ifndef __VECTOR__
#define __VECTOR__

class Vector{
  int v[6];
  int nelem;
public:

  // Constructor a partir de un vector no ordenado
  Vector(int l[6]):nelem(6){
    for (int i = 0; i < 6; i++)
      v[i] = l[i];
  }

  // Asigna l a v
  void reinicia(int l[6]){
    nelem = 6;
    for (int i = 0; i < 6; i++)
      v[i] = l[i];
  }

  // Borra el elemento en pos
  void borra(int pos);
  // Inserta n ordenadamente
  int inserta(int n);

  inline int operator[](int pos){return v[pos];}
  inline int size() const{return nelem;}

  // Devuelve posición de primer elemento útil para op
  inline bool inicial(int op) const{
    int i = 0;
    if(op > 1) // Si op es * o /
      while(v[i] == 1 && i < size())
        i++;
    return i;
  }

  // Avanza hasta el siguiente elemento no repetido
  inline bool avanza(int j) const{
    j++;
    while(v[j] == v[j-1] && j < size())
      j++;
    return j;
  }
};

#endif
