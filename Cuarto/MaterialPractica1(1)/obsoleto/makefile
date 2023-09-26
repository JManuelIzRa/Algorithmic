obj= main.o sistemaEcuaciones.o fibonacciRecursivo.o productoMatricesCuadradas.o ordenacionSeleccion.o
CC= g++
WARNING = -Wall
FLAGS = -lrt

todo: main.out 

sistemaEcuaciones.o: sistemaEcuaciones.cpp sistemaEcuaciones.hpp
	$(CC) -c sistemaEcuaciones.cpp $(WARNING)

fibonacciRecursivo.o:  fibonacciRecursivo.cpp fibonacciRecursivo.hpp
	$(CC) -c fibonacciRecursivo.cpp $(WARNING)

productoMatricesCuadradas.o: productoMatricesCuadradas.cpp productoMatricesCuadradas.hpp
	$(CC) -c productoMatricesCuadradas.cpp $(WARNING)

ordenacionSeleccion.o: ordenacionSeleccion.cpp ordenacionSeleccion.hpp
	$(CC) -c ordenacionSeleccion.cpp $(WARNING)

main.o: main.cpp
	$(CC) -c main.cpp $(WARNING)

main.out: $(obj)
	$(CC) $(obj) -o main.out $(WARNING) $(FLAGS)
	
.PHONY : clean
 
clean :
	-rm $(obj)
