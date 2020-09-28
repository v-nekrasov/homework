#pragma once
//Задача №15 сложный класс
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
class CMatrix
{	
	int **m; int n; 
	public:
	/*методы для сложного класса*/
	CMatrix(){SetZero();} //конструктор по умолчанию
	~CMatrix(){Clean();}  //деструктор
	CMatrix(int n);//конструктор c параметром создаёт матрицу заполненную случайно нулями и единицами
	CMatrix(const CMatrix &b){CopyOnly(b);}//конструктор копирования
	CMatrix(CMatrix &&b){CopyOnly_(b);}//конструктор перемещения
	CMatrix &operator=(const CMatrix &b){if(&b!=this){Clean(); CopyOnly(b);} return *this;}//оператор присваивания
	CMatrix &operator=(CMatrix &&b){if(&b!=this){CopyOnly_(b);} return *this;}//присваивание перемещением
	void Clean(){for(int i=0; i<n; i++) delete[] m[i]; delete[] m; SetZero();}	
	void SetZero(){m=NULL; n=0;}
	void CopyOnly(const CMatrix &b);
	void CopyOnly_(CMatrix &b){n=b.n; m=b.m; b.SetZero();}
	/*методы для решения задачи*/
	int size()const{return n;}
	CMatrix operator+(const CMatrix &c) const;
	CMatrix &operator++(void);
	CMatrix operator++(int);
	CMatrix &operator--(void);
	CMatrix operator--(int);
	friend ostream &operator<<(ostream &cout, const CMatrix &a);
};                    