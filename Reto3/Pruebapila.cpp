#include <iostream>
#include "Pila.h"
using namespace std;

int main() {
	Pila<int> p;
	for (int i = 0; i < 10; i++)
		p.poner(i);
	
	cout << "Se ha llenado la pila con " << p.elementos() << " elementos.\n";

	while (!p.vacia()) {
		cout << "Extraemos el elemento " << p.tope();
		p.quitar();
		cout << ". Quedan " << p.elementos() << " elementos.\n";
	}
}
