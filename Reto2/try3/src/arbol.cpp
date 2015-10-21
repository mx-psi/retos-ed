#include "arbol.h"
#include <iostream>

using namespace std;

int  Combinar(int *v, int n, int* & buffer)
{
  int tam=2*n*n-2*n;    // tamaño del vector de las combinaciones
  buffer=new int[tam];
  int cont=0;

  //Combinamos los elementos del vector "v" que nos pasan como parámetro para rellenar el "buffer".
  for(int i=0; i<n; i++)
  {
    for(int j=i+1; j<n; j++)
    {
      for(int k=0; k<4; k++)
      {
        if(k==0){buffer[cont]=v[i]+v[j];}

        if(k==1)
        {   if(v[j]>v[i]){buffer[cont]=v[j]-v[i];}
            else if(v[i]>v[j]){buffer[cont]=v[i]-v[j];}
        }

        if(k==2 && v[i]!=1 && v[j]!=1){buffer[cont]=v[i]*v[j];}

        if(k==3)
        {
            if(v[i]!=1 && v[j]!=1)
            {
              if(v[i]%v[j]==0){buffer[cont]=v[i]/v[j];}
              else if(v[j]%v[i]==0){buffer[cont]=v[j]/v[i];}
                  else{buffer[cont]=0;}
            }
        }

      cont++;
      }
    }
  }
return tam;
}

void Road(int i, int n, int * &road)
{
  int op=i%4; //Operación que se ha realizado para conseguir el elemento v[i];
  int cont=0;
  int elemento1=0;  //primer elemento de la combinación
  int elemento2=0;  // segundo elemento de la combinación

  //Buscamos los elementos que se han combinado para conseguir el elemento v[i];
  while(i>=cont)
  {
    elemento1++;     // indice del primer elemento de la combinación.
    cont+=4*(n-elemento1);
  }

  cont=cont-4*(n-elemento1);

  while(i>=cont)
  {
    cont+=4;
    elemento2++;  //indice del segundo elemento de la combinación.
  }

  elemento2+=elemento1;
  int* tmp=new int[3];

  tmp[0]=elemento1-1;
  tmp[1]=elemento2-1;
  road=tmp;
}

int  new_vec(int* v, int n, int *p, int i, int* &buffer)
{
  int tam;
  if(p[i]!=0)
  {
    int *tmp;
    Road(i,n,tmp);

    //Creamos el vector con los nuevos datos
    tam=n-1;
    buffer=new int[tam];
    buffer[0]=p[i];    //elemento que nos pasan como parámetro.
    int cont=1;

    for(int i=0; i<n; i++)
    {
      if(i!=tmp[0] && i!=tmp[1])
      {
        buffer[cont]=v[i];
        cont++;
      }
    }

  }

  else{tam=0;}

return tam;
}

int new_vec(int* v,int n,nodo nod, int * & buffer)
{
  int tam=n-1;    //tamaño del nuevo vector
  buffer=new int[tam];

  buffer[0]=nod.elemento;
  int cont=1;         // Acabamos de usar el primer elemento, la cuenta empieza en 1.

  for(int i=0; i<n; i++)
  {
    if(i!=nod.comb1 && i!=nod.comb2)
    {
      buffer[cont]=v[i];      //Rellenamos el buffer con los elementos de v que no se han usado para crear "nod.elemento"
      cont++;
    }
  }

return tam;
}

void Traza(int *v,int n,int i ,nodo * &traza, int& m)
{
  int *tmp;
  Road(i,n,tmp);

  traza[m].elemento=v[i];
  traza[m].comb1=tmp[0];
  traza[m].comb2=tmp[1];
  traza[m].op=i%4;
  m++;

}

bool Recorrer(int *v, int n, int meta, nodo * &traza,int& m, bool & encontrado, int &mejor_aprox)
{
  int *buffer;
  int tam=Combinar(v,n,buffer);
  for(int i=0; i<tam && !encontrado; i++)
  {
    if(buffer[i]==meta)
    {
      encontrado=true;
      Traza(buffer,n,i,traza,m);
    }


    else{

      if(Distancia(mejor_aprox,meta)>Distancia(buffer[i],meta)){mejor_aprox=buffer[i];}

      int *tmp;
      int n_tmp=new_vec(v,n,buffer,i,tmp);
      encontrado=Recorrer(tmp,n_tmp,meta,traza,m,encontrado,mejor_aprox);
      if(encontrado){Traza(buffer,n,i,traza,m);}
      delete [] tmp;
      }
  }

return encontrado;
}

void Imprime(int *v,nodo * traza, int i)
{
  if(traza[i].op==0)
  {cout <<traza[i].elemento<<"="<<v[traza[i].comb1]<<"+"<<v[traza[i].comb2];}

  if(traza[i].op==1)
  {
    if(v[traza[i].comb1]>v[traza[i].comb2]){cout <<traza[i].elemento<<"="<<v[traza[i].comb1]<<"-"<<v[traza[i].comb2];}
    else{cout <<traza[i].elemento<<"="<<v[traza[i].comb2]<<"-"<<v[traza[i].comb1];}
  }

  if(traza[i].op==2){cout <<traza[i].elemento<<"="<<v[traza[i].comb1]<<"*"<<v[traza[i].comb2];}

  if(traza[i].op==3){cout <<traza[i].elemento<<"="<<v[traza[i].comb1]<<"/"<<v[traza[i].comb2];}
}


void Preetyprint(int* v,int n,nodo *traza, int m)
{
  int *p=v;
  int*tmp=v;
  int tam=n;

  for(int i=m-1; i>=0; i--)
  {
    Imprime(p,traza,i);

    cout << "    { ";
    for(int j=0; j<tam; j++){cout<<p[j]<< " ";}
    cout <<"}"<< endl;
    tam=new_vec(p,tam,traza[i],tmp);
      if(i>m-1){delete [] p;}
    p=tmp;
  }

}
