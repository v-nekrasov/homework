//Задача №15
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1
using namespace std;
class CMatrix
{	
	int m[N][N]; int n=N; 
	public:
	CMatrix();//конструктор по умолчанию создаёт матрицу заполненную случайно нулями и единицами
	int size()const{return n;}
	CMatrix operator+(const CMatrix &b);
	friend ostream &operator<<(ostream &cout, const CMatrix &a);
};