mytask:main.o task.o read.o
	gcc main.o task.o read.o -o mytask

main.o:main.c matrix.h
	gcc -std=c11 -c main.c -o main.o

task.o:task.c matrix.h
	gcc -std=c11 -c task.c -o task.o

read.o:read.c matrix.h
	gcc -std=c11 -c read.c -o read.o
