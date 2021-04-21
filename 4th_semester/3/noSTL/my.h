#pragma once
//Задача №16 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#define P 31
using namespace std;
class CFactory;

class CPoly
{	
public:
	int *m; int n; 
	char FileName[20];
	/*методы для сложного класса*/
	CPoly(){SetZero(); memset(FileName, 0, 20);} //конструктор по умолчанию
	virtual ~CPoly(){Clean();}  //деструктор
	CPoly(int n){this->n = n; m = new int[n+1]; memset(m, 0, (n+1)*sizeof(int)); memset(FileName, 0, 20);};//конструктор c параметром создаёт многочлен степени n
	CPoly(const CPoly &b){memset(FileName, 0, 20); CopyOnly(b);}//конструктор копирования
/*!*/CPoly(CPoly &&b){memset(FileName, 0, 20); CopyOnly_(b);}//конструктор перемещения   
	CPoly &operator=(const CPoly &b){if(&b != this){Clean(); CopyOnly(b);} return *this;}//оператор присваивания
/*!*/CPoly &operator=(CPoly &&b){if(&b != this){Clean(); CopyOnly_(b);} return *this;}//присваивание перемещением
	void Clean(){delete[] m; SetZero();}	
	void SetZero(){m = NULL; n = 0;}
	void CopyOnly(const CPoly &b){n = b.n;  m = new int[n+1]; for(int i = 0; i < n+1; i++){m[i] = b.m[i];} if(strlen(FileName)==0){strcpy(FileName, b.FileName);}}
/*!*/void CopyOnly_(CPoly &b){n = b.n; m = b.m; if(strlen(FileName)==0){strcpy(FileName, b.FileName);} b.SetZero();}
	
	friend ostream &operator<<(ostream &cout, const CPoly &a);
	
	virtual void output()=0;
	static CPoly* create_by_factory(char *str, CFactory **f);

};

class CFactory
{public:
	virtual CPoly* create(int n)=0;
	virtual ~CFactory(){} 
};

class CData0: public CPoly
{public:
	CData0():CPoly(){}
    CData0(int n):CPoly(n){}
	CData0(const CPoly &b):CPoly(b){}
	void output();
};

class CData1: public CPoly
{public:
	CData1():CPoly(){}
    CData1(int n):CPoly(n){}
	CData1(const CPoly &b):CPoly(b){}
	void output();
};                    

class CFactoryCData0:public CFactory
{public:
	virtual CPoly* create(int n){
		CData0 *t = new CData0(n);
		return t; 
 	}
};
class CFactoryCData1:public CFactory
{public:
	virtual CPoly* create(int n){
		CData1 *t = new CData1(n);
		return t; 
	}
};

CData1 operator+(const CPoly &a, const CPoly &c);
CData1 operator-(const CPoly &a, const CPoly &c);
CData1 operator++(CPoly &a);
CData1 operator++(CPoly &a, int);
CData1 operator--(CPoly &a);
CData1 operator--(CPoly &a, int);             

CPoly ** read_data(const char *file, int &n, CFactory **f);

/*для работы с полем вычетов*/
int gcdex(int a, int b, int & x, int & y);
int inverse(int a);



