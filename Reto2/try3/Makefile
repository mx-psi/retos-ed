#MAKEFILE 
#AUTOR: DARIO SIERRA 
#FECHA: dom oct 18 11:59:41 CEST 2015 
#USO: MANEJA LA COMPILACION DEL PROYECTO cifras 

OBJ=obj/
SRC=src/
INC=include/
BIN=bin/


cifras: $(OBJ)arbol.o main.cpp 
	 g++ -I $(INC) -o cifras main.cpp $(OBJ)arbol.o
	mv cifras $(BIN)

$(OBJ)arbol.o: $(SRC)arbol.cpp $(INC)arbol.h 
	g++ -I $(INC) -c $(SRC)arbol.cpp 
	mv arbol.o $(OBJ) 


##############################################--LIMPIEZA--############################################################ 

clean:
	rm -f $(OBJ)* 
	rm -f doc/html/*

##############################################--DOCUMENTACION--######################################################### 

documentacion : 
	doxygen doc/doxys/Doxyfile

