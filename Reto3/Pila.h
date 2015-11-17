#ifndef __PILA_H__
#define __PILA_H__

#include <list>

template<class T>
class Pila {
private:
	std::list<T> lista;

public:
	Pila() {};
	Pila(const Pila& p) {
		lista = p.lista;
	}
	Pila& operator=(const Pila& p) {
		lista = p.lista;
	}
	bool vacia() const {
		return lista.empty();
	}
	const T& tope() const {
		return lista.front();
	}
	T& tope() {
		return lista.front();
	}
	void poner(const T& t) {
		lista.push_front(t);
	}
	void quitar() {
		lista.pop_front();
	}
	int elementos() const {
		return lista.size();
	}
};

#endif
