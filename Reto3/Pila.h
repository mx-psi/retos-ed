/**
  * @file Pila.h
  * @brief Fichero cabecera del TDA Pila (implementado con listas)
  *
  * Gestiona una secuencia de elementos con facilidades para la inserción y
  * borrado de elementos en la primera posición.
  */

#ifndef __PILA_H__
#define __PILA_H__

#include <list>

/**
  *  @brief T.D.A. Pila
  *
  *
  * Una instancia @e p del tipo de dato abstracto Pila_max sobre un dominio @e T es
  * una sucesión finita de elementos del mismo con un funcionamiento @e LIFO
  * (Last In, First Out}). En una pila, las operaciones de inserción, borrado
  * y consulta tienen lugar en uno de los extremos, denominado @e tope de la pila.
  * Una pila longitud @e n la denotamos
  *
  * - <a1,a2,a3,..,an>
  *
  * Tendremos acceso únicamente al elemento del @e Tope,
  * es decir, a @e an, y sólo podremos borrar, insertar o consultar esa posición.
  *
  * Si n=0 diremos que la pila está vacía.
  *
  * El espacio requerido para el almacenamiento es O(n), donde n es el número
  * de elementos de la pila.
  *
  * @example PruebaPila.cpp
  */

template<class T>
class Pila {
private:
  std::list<T> lista; /**< Elementos de la pila */

public:
/**
  * @brief Constructor por defecto.
  */
  Pila() {};

  /**
    * @brief Constructor de copia.
    */
  Pila(const Pila& p) {
    lista = p.lista;
  }

  /**
    * @brief Operador de asignación.
    */
  Pila& operator=(const Pila& p) {
    lista = p.lista;
  }

  /**
    * @brief Indica si la pila está vacía.
    * @return Si la pila está vacía
    */
  bool vacia() const {
    return lista.empty();
  }

  /**
    * @brief Devuelve el elemento en el tope (versión constante).
    * @return Elemento del tope
    */
  const T& tope() const {
    return lista.front();
  }

  /**
    * @brief Devuelve el elemento en el tope (versión no constante).
    * @return Elemento del tope
    */
  T& tope() {
    return lista.front();
  }

  /**
    * @brief Pone un elemento en el tope.
    * @param t Elemento a poner
    */
  void poner(const T& t) {
    lista.push_front(t);
  }

  /**
    * @brief Elimina el elemento en el tope.
    */
  void quitar() {
    lista.pop_front();
  }

  /**
    * @brief Obtiene el tamaño de la pila.
    * @return Tamaño de la pila
    */
  int elementos() const {
    return lista.size();	// A partir de C++11 es O(1). Antes, O(n)
  }
};

#endif
