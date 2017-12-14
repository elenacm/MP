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
OPT=-Wall -g
# Nombre de la práctica
PRJ=practica2

# Las macros se usan en las reglas del makefile como si fuesen variables
# que se sustituyen por su valor definido anteriormente
all : $(BIN)/byte 

# incluir las reglas que faltan

clean: 
	rm -f $(OBJ)/*.o $(BIN)/* $(LIB)/* $(ZIP)/*
	
zip: clean
	zip -r $(ZIP)/$(PRJ).zip *

