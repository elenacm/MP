# Definición de macros para definir las carpetas de trabajo
BIN=./bin
OBJ=./obj
SRC=./src
INC=./include
LIB=./lib
ZIP=./zip
# Opciones de compilación
# -Wall muestra todas las advertencias
# -g compila en modo "depuración"
OPT=-Wall -g -O2
# Nombre de la práctica
PRJ=practica5

# Las macros se usan en las reglas del makefile como si fuesen variables
# que se sustituyen por su valor definido anteriormente
all: $(BIN)/testarteASCII $(BIN)/testplano $(BIN)/testimagen
testimagen: $(BIN)/testimagen
testplano: $(BIN)/testplano
testarteASCII: $(BIN)/testarteASCII

#Compilamos testimagen.cpp
$(BIN)/testimagen : $(OBJ)/testimagen.o $(LIB)/libimagen.a
	g++ $(OPT) $(OBJ)/testimagen.o -o $(BIN)/testimagen -l imagen -L $(LIB)

$(OBJ)/testimagen.o : $(SRC)/testimagen.cpp $(INC)/imagen.h
	g++ $(OPT) -c $(SRC)/testimagen.cpp -o $(OBJ)/testimagen.o -I $(INC)

#Compilamos testplano.cpp
$(BIN)/testplano : $(OBJ)/testplano.o $(LIB)/libimagen.a
	g++ $(OPT) $(OBJ)/testplano.o -o $(BIN)/testplano -l imagen -L $(LIB)

$(OBJ)/testplano.o : $(SRC)/testplano.cpp $(INC)/imagen.h
	g++ $(OPT) -c $(SRC)/testplano.cpp -o $(OBJ)/testplano.o -I $(INC)

#Compilamos testarteASCII.cpp
$(BIN)/testarteASCII : $(OBJ)/testarteASCII.o $(LIB)/libimagen.a
	g++ $(OPT) $(OBJ)/testarteASCII.o -o $(BIN)/testarteASCII -l imagen -L $(LIB)

$(OBJ)/testarteASCII.o : $(SRC)/testarteASCII.cpp $(INC)/imagen.h
	g++ $(OPT) -c $(SRC)/testarteASCII.cpp -o $(OBJ)/testarteASCII.o -I $(INC)

#Compilamos la clase Byte: byte.cpp
$(OBJ)/byte.o : $(SRC)/byte.cpp $(INC)/byte.h
	g++ $(OPT) -c $(SRC)/byte.cpp -o $(OBJ)/byte.o -I $(INC)

#Compilamos el pgm.cpp
$(OBJ)/pgm.o : $(SRC)/pgm.cpp $(INC)/pgm.h
	g++ $(OPT) -c $(SRC)/pgm.cpp -o $(OBJ)/pgm.o -I $(INC)

#Compilamos la clase imagen: imagen.cpp
$(OBJ)/imagen.o : $(SRC)/imagen.cpp $(INC)/byte.h $(INC)/imagen.h $(INC)/pgm.h
	g++ $(OPT) -c $(SRC)/imagen.cpp -o $(OBJ)/imagen.o -I $(INC)

#Creamos la biblioteca: libimagen.a
$(LIB)/libimagen.a : $(OBJ)/byte.o $(OBJ)/imagen.o $(OBJ)/pgm.o
	ar -rvs $(LIB)/libimagen.a $(OBJ)/byte.o $(OBJ)/imagen.o $(OBJ)/pgm.o

clean:
	rm -f $(OBJ)/*.o $(BIN)/* $(LIB)/* $(ZIP)/*

zip: clean
	zip -r $(ZIP)/$(PRJ).zip *
