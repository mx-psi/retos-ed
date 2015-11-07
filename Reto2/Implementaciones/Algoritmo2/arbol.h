#ifndef _ARBOL_H
#define  _ARBOL_H

#include <iostream>
using namespace std;

/**
  @file arbol.h
  @brief Fichero de cabecera

    *Las funciones en el documentadas resuelven el reto de las cifras.

    @author Darío Sierra
    @dato 3 de noviembre de 2015

*/

/**
  @brief Estructura creada para la devolución de las operaciones una vez allado el elemento "meta".
  @param elemento guarda el resultado de una operación.
  @param comb1 guarda el primer operando.
  @param comb2 guarda el segundo operando.
  @param op guarda la operación : 0 suma, 1 resta, 2 multiplicación, 3 división.

*/

struct nodo
{
  int elemento;
  int comb1;
  int comb2;
  int op;
};

/**
  @brief Función destinada a coger el elemento p[i] junto a los v[j] que no se usaron para crearlo y
        devolverlo en el vector "buffer"
  @param v vector inicial.
  @param n tamaño del vector v.
  @param p vector cuyos elementos son combinación de los v[i].
  @param i indice del primer elemento que tendrá el vector "buffer".
  @return tamaño del vector "buffer".
*/

int  new_vec(int* v, int n, int *p, int i, int* &buffer);

/**
  @brief Función modificada para usar una estructura que contiene ya el elemento a añadir al nuevo vector
        y los índices de los padres, usada para la impresión de las operaciones.
  @see Preetyprint
*/
int new_vec(int* v,int n,nodo nod, int * & buffer);

/**
  @brief Función destinada a recorrer de manera jeráquica los vectores que sean combinación de los de
        "v".
  @param v vector inicial.
  @param n tamaño del vector v.
  @param meta número que buscamos.
  @param traza vector en el que, de haber encontrado el elemento, guardamos las operaciones efectuadas.
  @param m tamaño del vector "traza".
  @param encontrado booleano que determinará si hemos encontrado la meta
  @param mejor_aprox entero que guardará la mejor aproximación.
  @pre La función no hace comprobaciones en cuanto a tamaños; si le decimos que encontrado= true,
      no lo buscara etc.. Inicializar de manera adecuada los valores que han de pasársele.

*/

bool Recorrer(int *v, int n, int meta, nodo * &traza,int& m, bool & encontrado,int &mejor_aprox);

/**
  @brief Modificación de la función "Recorrer", busca todos los números en el rango [100,1000].
        Si el elemento procesado está en ese rango marca la posición buffer[i]=true;
  @see Recorrer
  @param buffer vector de booleanos inicializados a false, que recorremos en cada iteración.

*/
bool Rec_Magic(int *v, int n, bool &encontrados,bool * &buffer, int m);

/**
  @brief Recorre un vector de bool pasados como parámetro
  @return devuelve false si alguno se encuentra a false, true de lo contrario.
*/
bool Restantes_magic(bool *magicbuffer, int m);

/**
  @brief Recibe un vector inicial "v"  y copia en "buffer" los resultados de operar sus elementos.
        Asigna un "0" a las operaciones no válidas.
  @see Recorrer
  @return tamaño de vector "buffer".

*/
int Combinar(int *v, int n, int * & buffer);

/**
  @brief Analiza el indice de un elemento creado por la función Combinar y devuelve que dos elementos
          del vector inicial se usaro para crearlo.
  @see Traza
  @return tamaño del vector = 2.

*/

void Road(int i, int n, int *&road);

/**
  @brief Guarda en el vector "traza" los elementos y operaciones usados para llegar a la "meta"
  @see Recorrer
  @see Road

*/
void Traza(int *v, int n, int i, nodo *&traza, int &m);

/**
  @brief Imprime los elementos del vector usados para llegar a la meta por pantalla.
*/

void Prettyprint(int* v,int n,nodo *traza, int m);

/**
  @brief Función auxiliar usada por Prettyprint
  @see Prettyprint
*/

void Imprime(int *v,nodo * traza, int i);

/**
  @brief Devuelve todas las combinaciones mágicas de 6 elementos del vector v.
  @pre Las imprime por pantalla, si las queremos en un archivo debemos usar >>fichero.txt.

*/

void WhatMagic(int *v, int n);

inline int Distancia(int x, int y)
{
  if(x>=y){return x-y;}

  else{return y-x;}
}

#endif
