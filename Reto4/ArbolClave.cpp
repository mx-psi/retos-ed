#include "ArbolBinario.h"
using namespace std;


template<class Tipo>
class GuardaArboles {
private:
  const ArbolBinario<Tipo>* arbol;
  ostream& os;

public:
  // Constructor. Determina la salida a la que se manda y el árbol que se guardará
  GuardaArboles(ostream& o, const ArbolBinario<Tipo>* a) :os(o), arbol(a) {}

  // Añade bits a la secuencia
  void GuardaBits(const typename ArbolBinario<Tipo>::Nodo& n, unsigned char& c, int& pos) {
    /* Añade un bit que indica si cada posible hijo existe */
    bool izq = arbol->izquierda(n) != 0;
    bool der = arbol->derecha(n) != 0;
    if (izq)
      c |= (0x80 >> pos);
    if (der)
      c |= (0x40 >> pos);

    pos += 2;
    /* Si se ha completado un byte, lo escribe */
    if (pos == 8) {
      pos = 0;
      os.put(c);
      c = 0;
    }

    /* Sigue recorriendo el árbol en preorden */
    if (izq)
      GuardaBits(arbol->izquierda(n), c, pos);
    if (der)
      GuardaBits(arbol->derecha(n), c, pos);
  }

  // Guarda la secuencia de bits que identifica la estructura del árbol
  void GuardaClave() {
    unsigned char c = 0;
    int pos = 0;
    GuardaBits(arbol->raiz(), c, pos);
    if (pos != 0)  // Si esto es true, hay un fragmento a medias sin escribir aún
      os.put(c);
  }

  // Guarda las etiquetas
  void GuardaElementos(const typename ArbolBinario<Tipo>::Nodo& n) {
    if (n != 0) {
      /* Añade la etiqueta del nodo actual */
      Tipo et = arbol->etiqueta(n);
      os.write(reinterpret_cast<const char *>(&et), sizeof(et));
      /* Prosigue en preorden */
      GuardaElementos(arbol->izquierda(n));
      GuardaElementos(arbol->derecha(n));
    }
  }

  // Guarda el árbol en la salida escogida
  void Guarda() {
    GuardaClave();
    GuardaElementos(arbol->raiz());
  }
};


template<class Tipo>
class LeeArboles {
private:
  ArbolBinario<Tipo>* arbol;
  istream& is;

public:
  // Constructor. Determina la entrada desde donde se lee y el árbol en que se guardará
  LeeArboles(istream& i, ArbolBinario<Tipo>* a) :is(i), arbol(a) {};

  // Añade nodos al árbol
  void AvanzaArmazon(const typename ArbolBinario<Tipo>::Nodo& n, char& c, int& pos) {
    /* Si ya se había aplicado completamente el byte anterior, lee otro */
    if (pos == 8) {
      pos = 0;
      is.get(c);
    }

    /* Añade (o no) nodos según los datos */
    bool izq = c & (0x80 >> pos);
    bool der = c & (0x40 >> pos);

    if (izq) {
      ArbolBinario<Tipo> nuevo(0);
      arbol->insertar_izquierda(n, nuevo);
    }
    if (der) {
      ArbolBinario<Tipo> nuevo(0);
      arbol->insertar_derecha(n, nuevo);
    }
    pos += 2;

    /* Sigue generando la estructura en preorden */
    if (izq)
      AvanzaArmazon(arbol->izquierda(n), c, pos);
    if (der)
      AvanzaArmazon(arbol->derecha(n), c, pos);
  }

  // Crea la estructura del árbol (con etiquetas inválidas que se asignarán correctamente después)
  void CreaArmazon() {
    Tipo nuevo; // Valor por defecto
    arbol->AsignaRaiz(nuevo);
    char c = 0;
    int pos = 8;
    AvanzaArmazon(arbol->raiz(), c, pos);
  }

  // Obtiene el siguiente nodo en preorden
  void Siguiente(typename ArbolBinario<Tipo>::Nodo& n) {
    if (arbol->izquierda(n) != 0)
      n = arbol->izquierda(n);
    else if (arbol->derecha(n) != 0)
      n = arbol->derecha(n);

    else {
      while (arbol->padre(n) != 0 &&
        (arbol->derecha(arbol->padre(n)) == n || arbol->derecha(arbol->padre(n)) == 0))
        n = arbol->padre(n);
      if (arbol->padre(n) == 0)
        n = 0;
      else
        n = arbol->derecha(arbol->padre(n));
    }
  }

  // Sustituye las etiquetas inválidas por las correctas
  void RellenaArmazon() {
    typename ArbolBinario<Tipo>::Nodo n = arbol->raiz();
    while (n != 0) {
      Tipo et;
      is.read((char*)&et, sizeof(et));
      n->etiqueta = et;
      Siguiente(n);
    }
  }

  // Obtiene el árbol a partir de datos de la entrada escogida
  void Lee() {
    CreaArmazon();
    RellenaArmazon();
  }
};
