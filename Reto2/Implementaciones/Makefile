CXX = g++
CPPFLAGS = -O3 -std=c++11

all: Algoritmo1 Algoritmo2 Algoritmo3

# Compilación de módulos
Algoritmo1.out: Algoritmo1/Algoritmo1.cpp
	$(CXX) $(CPPFLAGS) -o $@ main.cpp $^

Algoritmo2.out: Algoritmo2/Algoritmo2.cpp Algoritmo2/arbol.cpp
	$(CXX) $(CPPFLAGS) -o $@ main.cpp $^

Algoritmo3.out: Algoritmo3/Algoritmo3.cpp Algoritmo3/pila.cpp Algoritmo3/vector.cpp
	$(CXX) $(CPPFLAGS) -o $@ main.cpp $^
