obj= main.o funciones.o sistemaEcuaciones.o quicksort.o fusion.o
CC= g++
WARNING = -Wall
FLAGS = -lrt

todo: main.out 

funciones.o: funciones.cpp funciones.h
	$(CC) -c funciones.cpp $(WARNING)

sistemaEcuaciones.o:  sistemaEcuaciones.cpp sistemaEcuaciones.hpp
	$(CC) -c sistemaEcuaciones.cpp $(WARNING)

quicksort.o: quicksort.cpp quicksort.h
	$(CC) -c quicksort.cpp $(WARNING)

fusion.o: fusion.cpp fusion.h
	$(CC) -c fusion.cpp $(WARNING)

main.o: main.cpp
	$(CC) -c main.cpp $(WARNING)

main.out: $(obj)
	$(CC) $(obj) -o main.out $(WARNING) $(FLAGS)
	
.PHONY : clean
 
clean :
	-rm $(obj)
