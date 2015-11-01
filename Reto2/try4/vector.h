#include <iostream>
using namespace std;

class Vector{
  int v[7];
  int nelem;
public:

  // Constructor a partir de un vector
  Vector(int l[6]):nelem(6){
    for (int i = 0; i < 6; i++)
      v[i] = l[i];
  }

  void borra(int pos);
  int inserta(int n);

  inline int operator[](int pos){return v[pos];}
  inline int size() const{return nelem;}
  inline bool no_usa_uno(int op) const{return (op > 1 && v[0] == 1);}
  inline bool dup(int j) const{return 1 + (v[j] == v[j+1]);}
};

ostream& operator<<(ostream& os, Vector& v);
