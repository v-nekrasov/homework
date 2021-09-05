#include "my.h"
//n=5
int main()
{
	CComplexVector a, b;//создаём два вектора, печатаем их длину, заполняем их "лесенкой" от 0 до 4
	cout << "Length=" << a.len() << endl;
	for(int i = 0; i<a.len(); i++)
		a[i] = CComplex(i, i);        //тут работает operator[]
	for(int i = 0; i<b.len(); i++)
		b[i] = CComplex(b.len()-1-i, b.len()-1-i); //тут работает operator[]
	cout << "a=" << endl << a << "b=" << endl << b;
	cout << "a+b=" << endl << (a+b); //тестируем сложение, вычитание, скалярное произведение
	cout << "a-b=" << endl << (a-b);
	cout << "a*b = " << a*b;
	return 0;
}