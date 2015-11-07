#ifndef _ARBOL_H
#define  _ARBOL_H


struct nodo
{
  int elemento;
  int comb1;
  int comb2;
  int op;
};


int  new_vec(int* v, int n, int *p, int i, int* &buffer);

int new_vec(int v,int n,nodo nod, int * & buffer);

bool Recorrer(int *v, int n, int meta, nodo * &traza,int& m, bool & encontrado,int &mejor_aprox);

int Combinar(int *v, int n, int * & buffer);

void Road(int i, int n, int *&road);

void Traza(int *v, int n, int i, nodo *&traza, int &m);

void Preetyprint(int* v,int n,nodo *traza, int m);

inline int Distancia(int x, int y)
{
  if(x>=y){return x-y;}

  else{return y-x;}
}

#endif
