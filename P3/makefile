obj= funciones.o
CC= g++
WARNING = -Wall
FLAGS = -lrt

todo: main.out 

funciones.o: funciones.cpp funciones.h
	$(CC) -c funciones.cpp $(WARNING)

main.out: $(obj) main.cpp
	$(CC) main.cpp $(obj) -o main.out $(WARNING) $(FLAGS)
	
.PHONY : clean
 
clean :
	-rm $(obj)