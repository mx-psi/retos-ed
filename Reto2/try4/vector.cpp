#include "vector.h"
#include <iostream>
#include <cassert>
using namespace std;

ostream& operator<<(ostream& os, Vector& v){
  os << "[";
  for (int i = 0; i < v.size(); i++)
    os << v[i] << (i+1!=v.size()?",":"");
  os << "]";
  return os;
}

//Borra el elemento en la posición pos
void Vector::borra(int pos){
  assert(nelem>0);
  for(int i = pos; i < nelem; i++)
    v[i] = v[i+1];
  nelem--;
}

// Inserta un elemento ordenadamente
int Vector::inserta(int n){
  assert(nelem<6);
  int i;

  for(i = 0; i < nelem; i++)
    if(v[i] > n)
      break;

  for(int j = nelem; j > i; j--)
    v[j] = v[j-1];

  v[i] = n;
  nelem++;
  return i;
}
