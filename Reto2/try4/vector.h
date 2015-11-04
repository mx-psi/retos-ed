#include <iostream>
#include <algorithm>

class Vector{
  int v[6];
  int nelem;
public:

  // Constructor a partir de un vector no ordenado
  Vector(int l[6]):nelem(6){
    std::sort(l, l+6);
    for (int i = 0; i < 6; i++)
      v[i] = l[i];
  }

  void borra(int pos);
  int inserta(int n);

  inline int operator[](int pos){return v[pos];}
  inline int size() const{return nelem;}

  inline bool no_usa_uno(int op) const{
    int i = 0;
    if(op > 1)
      while(v[i] == 1)
        i++;
    return i;
  }

  inline bool dup(int j) const{
    j++;
    while(v[j] == v[j-1] && j < nelem)
      j++;
    return j;
  }
};

std::ostream& operator<<(std::ostream& os, Vector& v);
