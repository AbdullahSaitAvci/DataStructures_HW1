all: derle bagla calistir

derle:
	g++ -c -I "./include" ./src/App.cpp             -o ./lib/App.o
	g++ -c -I "./include" ./src/DNode.cpp           -o ./lib/DNode.o
	g++ -c -I "./include" ./src/DoublyLinkedList.cpp -o ./lib/DoublyLinkedList.o
	g++ -c -I "./include" ./src/Exception.cpp       -o ./lib/Exception.o
	g++ -c -I "./include" ./src/Iterator.cpp        -o ./lib/Iterator.o
	g++ -c -I "./include" ./src/LinkedList.cpp      -o ./lib/LinkedList.o
	g++ -c -I "./include" ./src/Node.cpp            -o ./lib/Node.o
	g++ -c -I "./include" ./src/NoSuchElement.cpp   -o ./lib/NoSuchElement.o
	g++ -c -I "./include" ./src/Rectangle.cpp       -o ./lib/Rectangle.o
	g++ -c -I "./include" ./src/Screen.cpp          -o ./lib/Screen.o
	g++ -c -I "./include" ./src/Shape.cpp           -o ./lib/Shape.o
	g++ -c -I "./include" ./src/Triangle.cpp        -o ./lib/Triangle.o
	g++ -c -I "./include" ./src/Star.cpp          -o ./lib/Star.o
	g++ -c -I "./include" ./src/Test.cpp            -o ./lib/Test.o

bagla:
	g++ ./lib/App.o ./lib/DNode.o ./lib/DoublyLinkedList.o ./lib/Exception.o \
	    ./lib/Iterator.o ./lib/LinkedList.o ./lib/Node.o ./lib/NoSuchElement.o \
	    ./lib/Rectangle.o ./lib/Screen.o ./lib/Shape.o ./lib/Triangle.o \
	    ./lib/Star.o ./lib/Test.o -o ./bin/program

calistir:
	./bin/program
