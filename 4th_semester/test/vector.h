#pragma once
class Child;
class Base
{
public:
 	int *m; int n;
	Base(){SetZero();}
	Base(int n){this->n = n; m = new int[n];}
	virtual ~Base(){Clean();}
	Base(const Base &b){CopyOnly(b);}
	Base(Base&&b){CopyOnly_(b);}//move-constructor
	Base &operator=(const Base &b){if(this != &b){Clean(); CopyOnly(b);} return *this;}
	Base &operator=(Base &&b){if(this != &b){Clean(); CopyOnly_(b);} return *this;}//move-assignment
	void Clean(){delete[] m; SetZero();}
	void SetZero(){m = NULL; n = 0;}
	void CopyOnly(const Base &b){n = b.n; m = new int[n]; for(int i = 0; i < n; i++){m[i] = b.m[i];}}
	void CopyOnly_(Base &b){n = b.n; m = b.m; b.SetZero();}
	void print()const{for(int i = 0; i < n; i++) cout << m[i] << " ";}
	int length()const{return n;}
	friend ostream &operator<<(ostream &cout, const Base &v);	
	void Delete(int t);
	Child operator++(void);
	Child operator++(int);
/*	CMatrix operator+(const CMatrix &c) const;*/
	virtual bool test(int t);
};
                           
class Child: public Base
{public:
	Child():Base(){}
    Child(int n):Base(n){}
	Child(const Base &b):Base(b){}
	bool test(int t);
};

Child operator+(const Base &a,const Base &b);
