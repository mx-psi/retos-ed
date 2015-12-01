#include "ArbolBinario.h"
typedef int Tipo;
typedef ArbolBinario<Tipo> AB;
using namespace std;

class GuardaArboles {
private:
  const AB* arbol;
  ostream& os;
  
public:
  GuardaArboles(ostream& o, const AB* a) :os(o), arbol(a) {};

  void GuardaBits(const AB::Nodo& n, unsigned char& c, int& pos) {
    bool izq = arbol->izquierda(n) != 0;
    bool der = arbol->derecha(n) != 0;
    if (izq)
    c |= (0x80 >> pos);
    if (der)
    c |= (0x40 >> pos);
    pos += 2;
    if (pos == 8) {
  	  pos = 0;
      os.put(c);
	  c = 0;
    }
    if (izq)
      GuardaBits(arbol->izquierda(n), c, pos);
    if (der)
      GuardaBits(arbol->derecha(n), c, pos);
  }

  void GuardaClave() {
    unsigned char c = 0;
    int pos = 0;
    GuardaBits(arbol->raiz(), c, pos);
    if (pos != 0)  // Si esto es true, hay un fragmento a medias sin escribir aún
      os.put(c);
  }

  void GuardaElementos(const AB::Nodo& n) {
    if (n != 0) {
      Tipo et = arbol->etiqueta(n);
      os.write(reinterpret_cast<const char *>(&et), sizeof(et));
	  GuardaElementos(arbol->izquierda(n));
	  GuardaElementos(arbol->derecha(n));
    }
  }

  void Guarda() {
    GuardaClave();
    GuardaElementos(arbol->raiz());
  }
};



class LeeArboles {
private:
  AB* arbol;
  istream& is;
  
public:
  LeeArboles(istream& i, AB* a) :is(i), arbol(a) {};

  void AvanzaArmazon(const AB::Nodo& n, char& c, int& pos) {
    if (pos == 8) {
      pos = 0;
      is.get(c);
	}
	bool izq = c & (0x80 >> pos);
	bool der = c & (0x40 >> pos);

	if (izq) {
      AB nuevo(0);
      arbol->insertar_izquierda(n, nuevo);
	}
	if (der) {
      AB nuevo(0);
      arbol->insertar_derecha(n, nuevo);
	}
	pos += 2;
	if (izq)
      AvanzaArmazon(arbol->izquierda(n), c, pos);
	if (der)
      AvanzaArmazon(arbol->derecha(n), c, pos);
  }
  
  // Crea el árbol con etiquetas inválidas (se asignarán correctamente después)
  void CreaArmazon() {
    arbol->AsignaRaiz(0);
    char c = 0;
    int pos = 8;
    AvanzaArmazon(arbol->raiz(), c, pos);
  }
  
  // Obtiene el siguiente nodo en preorden
  void Siguiente(AB::Nodo& n) {
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
  
  void AvanzaRelleno(AB::Nodo n) {
    while (n != 0) {
      Tipo et;
      is.read((char*)&et, sizeof(et));
      n->etiqueta = et;
	  Siguiente(n);
	}
  }

  // Sustituye las etiquetas inválidas por las correctas
  void RellenaArmazon() {
    AvanzaRelleno(arbol->raiz());
  }
  
  void Lee() {
    arbol->clear();
    CreaArmazon();
	RellenaArmazon();
  }
};

