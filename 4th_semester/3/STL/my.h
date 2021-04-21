#pragma once
//Задача №16 STL-style
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <time.h>

#define P 2129
using namespace std;
class CFactory;

class CPoly
{	
public:
	vector<int> m; string FileName;

	CPoly(){} 
	virtual ~CPoly(){} 
	CPoly(int n){FileName = ""; m.resize(n+1); for(auto it = m.begin(); it != m.end(); ++it){*it = 0;}};
	CPoly(const CPoly &b)=default;//{FileName = b.FileName; m = b.m;}
/*!*/CPoly(CPoly &&b){FileName = move(b.FileName); m = move(b.m);}   
	CPoly &operator=(const CPoly &b)=default;//{if(&b != this){m = b.m; if(FileName == ""){FileName = b.FileName;}} return *this;}
/*!*/CPoly &operator=(CPoly &&b){if(&b != this){m = move(b.m); if(FileName == ""){FileName = move(b.FileName);}} return *this;}

	friend ostream &operator<<(ostream &cout, const CPoly &a);
	
	virtual void output()=0;
	static int read_data(const char *file, vector<CPoly*> &arr, vector<CFactory*> &f);
};

class CFactory
{public:
	virtual CPoly* create()=0;
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
	virtual CPoly* create(){
		CData0 *t = new CData0();
		return t; 
 	}
};
class CFactoryCData1:public CFactory
{public:
	virtual CPoly* create(){
		CData1 *t = new CData1();
		return t; 
	}
};

CData1 operator+(const CPoly &a, const CPoly &c);
CData1 operator-(const CPoly &a, const CPoly &c);
CData1 operator++(CPoly &a);
CData1 operator++(CPoly &a, int);
CData1 operator--(CPoly &a);
CData1 operator--(CPoly &a, int);             


/*для работы с полем вычетов*/
int gcdex(int a, int b, int &x, int &y);
int inverse(int a);



