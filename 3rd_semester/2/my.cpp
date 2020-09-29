#include"my.h"

CMatrix::CMatrix(int n)
{
	this->n=n;
	m=new int*[n];
	for(int i=0; i<n; i++)
		m[i]=new int[n]; //отвели память 
	for(int i=0; i<n; i++) 
		for(int j=0; j<n; j++) 
			m[i][j]=rand()%2;
}

 
CMatrix CMatrix::operator+(const CMatrix &c) const// 
{ // будем использовать метод Гаусса
	CMatrix b=c;
	CMatrix a=*this;//работаем с a и b, чтобы не менять this и с
	int n1=a.n;
	int n2=b.n;
	int n0=a.n;//размер результата сложения
	if(n1>n2)//если первое слагаемое больше второго
	{	
		n0=n1;	
		CMatrix b_=b;//сохраняем данные для переотведения памяти
		b.Clean();
		b.n=n0;
		b.m=new int*[n0];
		for(int i=0; i<n0; i++)
			b.m[i]=new int[n0]; //отвели память 

		for(int i=0; i<n2; i++) 
			for(int j=0; j<n2; j++)
				b.m[i][j]=b_.m[i][j];//переписали старое

		for(int i=0; i<n1; i++) 
			for(int j=n2; j<n0; j++) 
				b.m[i][j]=0;//дозаполнили нулями
		for(int i=n2; i<n0; i++) 
			for(int j=0; j<n0; j++) 
				b.m[i][j]=0;//дозаполнили нулями
	}
	else if(n1<n2)//если второе слагаемое больше первого
	{
		n0=n2;
		CMatrix a_=a;
		a.Clean();
		a.n=n0;
		a.m=new int*[n0];
		for(int i=0; i<n0; i++)
			a.m[i]=new int[n0]; //отвели память

		for(int i=0; i<n1; i++) 
			for(int j=0; j<n1; j++) 
				a.m[i][j]=a_.m[i][j];//вернули старое
				
		for(int i=0; i<n2; i++) 
			for(int j=n1; j<n0; j++) 
				a.m[i][j]=0;//дозаполнили нулями
		for(int i=n1; i<n0; i++) 
			for(int j=0; j<n0; j++) 
				a.m[i][j]=0;//дозаполнили нулями
	}
	int i,j,k; 
	int **tmp;
	tmp=new int*[2*n0];
	for(int i=0; i<2*n0; i++)
		tmp[i]=new int[n0]; //отвели память   	
	CMatrix r(n0);

	for(i=0; i<n0; i++)//копируем в tmp две матрицы --- получаем систему пересечения (приписали вторую систему снизу) 
		for(j=0; j<n0; j++) 
	    	tmp[i][j]=a.m[i][j];
	for(i=0; i<n0; i++) 
		for(j=0; j<n0; j++) 
	    	tmp[i+n0][j]=b.m[i][j];

	/*далее --- метод Гаусса*/

	k=0;//в k-ую строку r будем записывать
	for(j=0; j<n0; j++)//идём по столбцам
	{	
		 for(i=0; i<2*n0; i++)
			if(tmp[i][j]==1) //встретили первый ненулевой эл-т в столбце
			{	
				for(int l=0; l<n0; l++)//берем эту строку в результат
					r.m[k][l]=tmp[i][l];
				k++;
				for(int p=i+1; p<2*n0; p++)//обнуляем столбец
					if(tmp[p][j]==1)
					{
						for(int l=0; l<n0; l++)//вычитаем i-ую строку из p-ой
							tmp[p][l]=abs(tmp[p][l]-tmp[i][l]);		
					}
				for(int l=0; l<n0; l++)//"стираем" строку --- больше её использовать не будем
					tmp[i][l]=2;
				break;	
			}
	}
	while(k<n0)
	{
		for(int l=0; l<n0; l++)//возможно, дописали нулевые строки
			r.m[k][l]=0;
		k++;	
	}
	//очистить память для буфера
	for(int i=0; i<2*n0; i++)
		delete[] tmp[i];
	delete[] tmp; tmp=NULL;	
	return r;
}

void CMatrix::CopyOnly(const CMatrix &b)
{
	n=b.n; 
	m=new int*[n]; 
	for(int i=0; i<n; i++) 
		m[i]=new int[n];                         
	for(int i=0; i<n; i++) 
		for(int j=0; j<n; j++) 
			m[i][j]=b.m[i][j];//скопировали матрицу
}

CMatrix&  CMatrix::operator++(void)//++a
{ 
	CMatrix a_=*this;
	Clean();
	n=a_.n+1;//увеличили размер
	m=new int*[n];
	for(int i=0; i<n; i++)
		m[i]=new int[n]; //отвели память    
	for(int i=0; i<n-1; i++) 
		for(int j=0; j<n-1; j++) 
			m[i][j]=a_.m[i][j];//вернули старое
	for(int i=0; i<n; i++)
	{ 
		m[i][n-1]=0;
		m[n-1][i]=0;
	}//дозаполнили нулями
	return *this; //возвращаем измененный объект
}
CMatrix CMatrix::operator++(int)//a++
{ 
	CMatrix a_=*this;//перед изменением делаем копию объекта
	Clean();
	n=a_.n+1;//увеличили размер	
	m=new int*[n];
	for(int i=0; i<n; i++)
		m[i]=new int[n]; //отвели память
	for(int i=0; i<n-1; i++) 
		for(int j=0; j<n-1; j++) 
			m[i][j]=a_.m[i][j];//вернули старое
	for(int i=0; i<n; i++)
	{ 
		m[i][n-1]=0;
		m[n-1][i]=0;
	}//дозаполнили нулями
	return a_;//возвращаем неизмененный объект
}
CMatrix&  CMatrix::operator--(void)//--a
{ 
	if(n>1) 
	{
		delete[] m[n-1];
		n--;
	}
	return *this; //возвращаем измененный объект
}
CMatrix CMatrix::operator--(int)//a--
{ 
	CMatrix tmp=*this; //перед изменением делаем копию объекта
	if(n>1) 
	{
		delete[] m[n-1];
		n--;
	}
	return tmp;//возвращаем неизмененный объект
}

ostream &operator<<(ostream &cout, const CMatrix &a)
{
	for(int i=0; i<a.size(); i++)
	{
		cout<<"| ";
		for(int j=0; j<a.size(); j++)
			cout<<a.m[i][j]<<" ";
		cout<<"|"<<endl;
	}
	return cout;
}