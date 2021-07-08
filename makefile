CXX=g++ -g

all: map.o mapTest
map.o: map.cpp map.h
	$(CXX) -c map.cpp

mapTest: mapTest.cpp map.o map.h
	$(CXX) mapTest.cpp map.o -lgtest -lpthread -o mapTest
	./mapTest
	
clean:
	rm -f *.o  mapTest

