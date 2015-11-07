#include "vector.h"

//Borra el elemento en la posición pos
void Vector::borra(int pos){
  for(int i = pos; i < nelem; i++)
    v[i] = v[i+1];
  nelem--;
}

// Inserta un elemento ordenadamente
int Vector::inserta(int n){
  int pos = 0, ini = v[0] < n, fin = nelem-1;

  while (ini <= fin) {
    pos = (ini+fin)/2;
    if (v[pos] < n)
      ini = pos+1;
    else
      fin = pos-1;
  }

  for(int j = nelem; j > ini; j--)
    v[j] = v[j-1];

  v[ini] = n;
  nelem++;
  return ini;
}
