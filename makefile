all: crossover.o myrand.o
	g++ crossover.o myrand.o -o crossoverTest
crossover.o: crossover.cpp
	g++ -c crossover.cpp
myrand.o: myrand.cpp myrand.h
	g++ -c myrand.cpp	
clean:
	rm *.o *.exe