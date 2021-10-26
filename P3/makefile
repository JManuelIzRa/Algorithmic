obj= main.o funciones.o
CC= g++
WARNING = -Wall
FLAGS = -lrt

todo: main.out 

main.o: main.cpp
	$(CC) -c main.cpp $(WARNING)

funciones.o: funciones.cpp funciones.h
	$(CC) -c funciones.cpp $(WARNING)

main.out: $(obj)
	$(CC) $(obj) -o main.out $(WARNING) $(FLAGS)
	
.PHONY : clean
 
clean :
	-rm $(obj)