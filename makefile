polycalculator: main.o linkedlist.o polycalculator.o
	g++ main.o linkedlist.o polycalculator.o -o polycalculator
main.o: main.cpp
	g++ -c main.cpp
linkedlist.o: linkedlist.cpp linkedlist.h
	g++ -c linkedlist.cpp
polycalculator.o: polycalculator.cpp polycalculator.h
	g++ -c polycalculator.cpp
clean: 
	rm polycalculator main.o linkedlist.o polycalculator.o