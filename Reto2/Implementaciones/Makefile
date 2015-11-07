CXX = g++
CPPFLAGS = -O3 -std=c++11
EXT = out

all: Algoritmo1.$(EXT) Algoritmo2.$(EXT) Algoritmo3.$(EXT) Algoritmo1magic.$(EXT)

# Compilación de módulos
Algoritmo1.$(EXT): Algoritmo1/Algoritmo1.cpp
	$(CXX) $(CPPFLAGS) -o $@ main.cpp $^

Algoritmo2.$(EXT): Algoritmo2/Algoritmo2.cpp Algoritmo2/arbol.cpp
	$(CXX) $(CPPFLAGS) -o $@ main.cpp $^

Algoritmo3.$(EXT): Algoritmo3/Algoritmo3.cpp Algoritmo3/pila.cpp Algoritmo3/vector.cpp
	$(CXX) $(CPPFLAGS) -o $@ main.cpp $^

Algoritmo1magic.$(EXT): Algoritmo1/Algoritmo1magic.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^