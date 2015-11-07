#include "arbol.h"
#include <iostream>

using namespace std;

int  Combinar(int *v, int n, int* & buffer)
{
  int tam=2*n*(n-1);    // tamaño del vector de las combinaciones
  buffer=new int[tam];
  int cont=0;

  //Combinamos los elementos del vector "v" que nos pasan como parámetro para rellenar el "buffer".
  for(int i=0; i<n; i++)
  {
    for(int j=i+1; j<n; j++)
    {
      for(int k=0; k<4; k++)
      {
        buffer[cont] = 0;
		
		if(k==0){buffer[cont]=v[i]+v[j];}

        else if(k==1)
        {   if(v[j]>v[i]){buffer[cont]=v[j]-v[i];}
            else{ buffer[cont]=v[i]-v[j];}
        }

        else if (v[i] != 1 && v[j] != 1)
            if(k==2)
                buffer[cont]=v[i]*v[j];
            else if(k==3)
            {
                if(v[i]%v[j]==0){buffer[cont]=v[i]/v[j];}
                else if(v[j]%v[i]==0){buffer[cont]=v[j]/v[i];}
            }

      if(buffer[cont]==v[i] || buffer[cont]==v[j])
            buffer[cont]=0;


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
    cont+=4*(n-elemento1);  //Vamos sumando hasta pasarnos
  }

  cont=cont-4*(n-elemento1);    //Retrocedemos al anterior

  while(i>=cont)
  {
    cont+=4;       //Vamos sumando hasta pasarnos.
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
      if(i!=tmp[0] && i!=tmp[1])  // Si el elemento es distinto de los que se usaron para
      {                           //crear el p[i] los añadimos
        buffer[cont]=v[i];
        cont++;
      }
    }

  }

  else{tam=0;buffer=0;}

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
  Road(i,n,tmp);  //Buscamos el índice de los elementos que se usaron para crear el "i".

  traza[m].elemento=v[i];   //Guardamos el elementos y los índices del  los "padres"
  traza[m].comb1=tmp[0];
  traza[m].comb2=tmp[1];
  traza[m].op=i%4;        //Guardamos la operación.
  m++;
  delete []tmp;
}

bool Recorrer(int *v, int n, int meta, nodo * &traza,int& m, bool & encontrado, int &mejor_aprox)
{
  int *buffer;
  int tam=Combinar(v,n,buffer);   //Creamos el vector de las combinaciones asociado a v

  for(int i=0; i<tam && !encontrado; i++)
  {
    if(buffer[i]==meta)     //Comprobamos si alguno es la meta, en cuyo caso salimos.
    {
      encontrado=true;
      Traza(buffer,n,i,traza,m);  //Guardamos el camino que hemos usado para llegar al elemento.
    }
  }

  for(int i=0; i<tam && !encontrado; i++)   // De no haberlo encontrado buscamos recorremos en profundidad.
  {

    if(Distancia(mejor_aprox,meta)>Distancia(buffer[i],meta)) //Vamos calculando la mejor aproximación.
      mejor_aprox=buffer[i];

    if(buffer[i]!=0)
    {
      for(int j=i+1; j<tam; j++)
      {
        if(buffer[i]==buffer[j])    // Dado un elemento buscamos sus copias y las igualamos a 0 para no recorrerlas.
          buffer[j]=0;
      }

      int *tmp;
      int n_tmp=new_vec(v,n,buffer,i,tmp);  //Creamos el nuevo vector con tmp[0]=buffer[i];
      encontrado=Recorrer(tmp,n_tmp,meta,traza,m,encontrado,mejor_aprox); //Recorremos el vector.

      if(encontrado)
      Traza(buffer,n,i,traza,m);    // Si lo hemos encontrado guardamos el camino que hemos seguido para llegar hasta él.

      delete [] tmp;
    }
  }
 
delete [] buffer;
return encontrado;
}
bool Restantes_magic(bool *magicbuffer, int m)
{
  bool terminado=true;

  for(int i=0; i<m && terminado; i++)
  {
    if(!magicbuffer[i]){terminado=false;}
  }
return terminado;
}


bool Rec_Magic(int *v, int n, bool &encontrados,bool* & magicbuffer, int m)
{
  int *buffer;
  int tam=Combinar(v,n,buffer);

    for(int i=0; i<tam && !encontrados; i++)
    {
      if(Restantes_magic(magicbuffer,m))
        encontrados=true;

      else
      {
        if(buffer[i]>=100 && buffer[i]<=1000){magicbuffer[buffer[i]-100]=true;}

        for(int j=i+1; j<tam ; j++)
        {
          if(buffer[i]==buffer[j] && buffer[i]!=0)
            buffer[j]=0;
        }

        if(buffer[i]!=0)
        {
          int *tmp;
          int n_tmp=new_vec(v,n,buffer,i,tmp);
          encontrados=Rec_Magic(tmp,n_tmp,encontrados,magicbuffer,m);
          delete [] tmp;
        }
      }
    }

  delete [] buffer;
  return encontrados;
}

void WhatMagic(int *v, int n)
{
  int *buffer=new int[6];
  int cont=0;
  bool encontrados=false;

  for(int i=0;i<n;i++)
    {
      buffer[0]=v[i];

      for(int j=i; j<n; j++)
      {
        buffer[1]=v[j];
        for(int k=j; k<n; k++)
        {
          buffer[2]=v[k];
          for(int a=k; a<n; a++)
          {
            buffer[3]=v[a];
            for(int b=a; b<n ;b++)
            {
              buffer[4]=v[b];
              for(int c=b; c<n;c++)
              {
                buffer[5]=v[c];
                encontrados=false;

                bool *magicbuffer=new bool[900];      //Creamos e inicializamos el vector a false.
                for(int i=0;i<900;i++){magicbuffer[i]=false;}

                bool magic=Rec_Magic(buffer,6,encontrados,magicbuffer,900);
/*
                if(magic)
                  {cout <<"ES MAGICA: , comb nº: "<< cont  << '\n'<< buffer[0]<<" "<<buffer[1]<<" "<<buffer[2]<<" "<<buffer[3]<<" "<<buffer[4]<<" "<<buffer[5]<<endl;}
                if(!magic)
                {cout << "NO ES MAGICA, comb nº: "<< cont<< '\n'<< buffer[0]<<" "<<buffer[1]<<" "<<buffer[2]<<" "<<buffer[3]<<" "<<buffer[4]<<" "<<buffer[5]<<endl;
                bool n_encontrado=false;
                  for(int d=0; d<900 && !n_encontrado; d++)
                    if(!magicbuffer[d]){n_encontrado=true;cout<< "No se encuentra el: "<< d+100<< endl;}
                }
*/
                delete [] magicbuffer;
                cont ++;
              }
            }
          }
        }
      }
    }
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

  if(traza[i].op==3)
  { if(v[traza[i].comb1]%v[traza[i].comb2]==0){cout <<traza[i].elemento<<"="<<v[traza[i].comb1]<<"/"<<v[traza[i].comb2];}
    else{cout <<traza[i].elemento<<"="<<v[traza[i].comb2]<<"/"<<v[traza[i].comb1];}
  }
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
