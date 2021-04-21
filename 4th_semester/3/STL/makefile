a:main.o my.o
	wg++ -fno-elide-constructors -std=c++11 -fopenmp my.o main.o
main.o: main.cpp my.h
	wg++ -fno-elide-constructors -std=c++11 -fopenmp main.cpp -c
my.o: my.cpp my.h
	wg++ -fno-elide-constructors -std=c++11 -fopenmp my.cpp -c
