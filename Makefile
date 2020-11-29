EXE = openFlights


EXE_OBJ = main.o
OBJS = graph.o main.o airport.o 


graph.o : graph.cpp graph.h
random.o : random.cpp random.h
main.o : main.cpp
airport.o : airport.cpp airport.h

