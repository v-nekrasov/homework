#include "my.h"                                                        
//cчитывание из файла и создание объектов
CPoly** read_data(const char *file, int &n, CFactory **f)
{
	int i = 0;
	n = 2;//размер массива объектов будем динамически увеличивать
	CPoly** arr;
	FILE *in = fopen(file, "rb");
	char buf[512];
	if (in == NULL) 
	{
		puts("ERR");
		return NULL;
	}
   	else
	{
		arr = new CPoly*[n];
		while(fgets(buf, 512, in))
			if(strlen(buf)>2)	
			{	
				if(i < n)
				{	
					CPoly* cr = CPoly::create_by_factory(buf, f);		
					if(cr) 
						arr[i++] = cr;
					else
					{	
						cout << "ERROR: BAD DATA IN " << i << " OBJECT" << endl;
						for(int j = 0; j < i; j++)
							delete arr[j];
						delete[] arr;
						fclose(in);
						return NULL;
					}	
				}
				else
				{
					CPoly* cr = CPoly::create_by_factory(buf, f);		
					if(cr) 
					{
					    CPoly **tmp = new CPoly*[2*n];
						for(int j = 0; j < n; j++)
							tmp[j] = arr[j];
						delete[] arr;
  						tmp[i++] = cr;
						arr = tmp;
						n *= 2;
					}
					else
					{	
						cout << "ERROR: BAD DATA IN " << i << " OBJECT" << endl;
						for(int j = 0; j < i; j++)
							delete arr[j];
						delete[] arr;
						fclose(in);
						return NULL;
					}        
				}
			}
		n = i;
		fclose(in);		
		return arr;				
	}
}

CPoly* CPoly::create_by_factory(char *buf, CFactory **f)
{ 
 	int Type, n = 2, x, *a, l, len = 1/*!!! 1 IF MINGW, 2 IF GNU G++*/; size_t i = 0; 
	char FileName[20], *buf_i;
	if((sscanf(buf, "%d%s%n", &Type, FileName, &l) != 2) || (Type != 1 && Type != 0)) 
		return NULL; 	
	a = new int[n];
	buf_i = buf + l;
	len += l;
	while(sscanf(buf_i, "%d%n", &x, &l) == 1)
	{   
	 	if(x < 0 || x >= P)
		{	
			delete[] a;	
			return NULL;
		}
		if((int)i < n)
			a[i++] = x%P;
		else
		{
		    int *tmp = new int[2*n];
            for(int j = 0; j < n; j++)
				tmp[j] = a[j];
			delete[] a;
			tmp[i++] = x%P;
			a = tmp;
			n *= 2; 
		}
		buf_i += l;
		len += l;
	}
	while(*buf_i == ' ' || *buf_i == '\r'){len++; buf_i++;}
	if(len != (int)strlen(buf))
	{	                
		delete[] a;
		return NULL;	
	}
  	n = (int)i;
	CPoly *r = f[Type]->create(n-1);
	strcpy(r->FileName, FileName);
	for(int j = 0; j < n; j++)                                        
		r->m[j] = a[j];					
	delete[] a;
	return r;
}
//-------------------------------------------------------------------
//виртуальный вывод
void CData0:: output()
{
	FILE *out = fopen(FileName, "a"); 	
	for(int i = 0; i < n; i++)
		fprintf(out, " %d*x^%d +", m[i], i); 
	fprintf(out, " %d*x^%d\n----\n", m[n], n); 
	fclose(out);
}

void CData1:: output()
{
	FILE *out = fopen(FileName, "a"); 	
	for(int i = 0; i < n; i++)
		fprintf(out, "%d*x^%d \n + \n", m[i], i); 
	fprintf(out, "%d*x^%d\n----\n", m[n], n); 
	fclose(out);

}
//-------------------------------------------------------------------
//Перегрузка операторов
CData1 operator+(const CPoly &a, const CPoly &c)
{              
	CData1 res;
	if(a.n != c.n)
	{
		if(a.n < c.n)
		{		
			res.n = c.n;
			res.m = new int[res.n + 1];
			for(int i = 0; i < res.n+1; i++)
				if(i <= a.n)
					res.m[i] = (a.m[i]+c.m[i])%P;
				else
					res.m[i] = (c.m[i])%P;			
		}
		else
		{
			res.n = a.n;
			res.m = new int[res.n + 1];
			for(int i = 0; i < res.n+1; i++)
				if(i <= c.n)
					res.m[i] = (a.m[i]+c.m[i])%P;
				else
					res.m[i] = (a.m[i])%P;
		}
	}
	else
	{
		res.n = a.n;
		res.m = new int[res.n + 1];
		for(int i = 0; i < res.n+1; i++)
			res.m[i]=(a.m[i]+c.m[i])%P;
	}
	return res;
}

CData1 operator-(const CPoly &a, const CPoly &c)
{
	CData1 res;
	if(a.n != c.n)
	{
		if(a.n < c.n)
		{		
		res.n = c.n;
			res.m = new int[res.n + 1];
			for(int i = 0; i < res.n + 1; i++)
				if(i <= a.n)
					res.m[i] = ((a.m[i]-c.m[i])%P > 0)?((a.m[i]-c.m[i])%P):(P+(a.m[i]-c.m[i])%P);
				else
					res.m[i] = (P-c.m[i])%P;			
		}
		else
		{
			res.n = a.n;
			res.m = new int[res.n + 1];
			for(int i = 0; i < res.n + 1; i++)
				if(i <= c.n)
					res.m[i] = ((a.m[i]-c.m[i])%P > 0)?((a.m[i]-c.m[i])%P):(P+(a.m[i]-c.m[i])%P);
				else
					res.m[i] = (a.m[i])%P;
		}
	}
	else
	{
		res.n = a.n;
		res.m = new int[res.n + 1];
		for(int i = 0; i < res.n+1; i++)
			res.m[i]=(a.m[i]-c.m[i])%P;
	}
	return res;         
}

CData1 operator++(CPoly &a)//++i
{                               
	CData1 tmp = a;
	a.Clean();
	a.n = tmp.n + 1;
	a.m = new int[a.n+1];
	a.m[0] = 0;
	for(int i = 1; i < a.n+1; i++)
		a.m[i] = (tmp.m[i-1] * inverse(i))%P;
	return a;
}

CData1 operator++(CPoly &a, int)//i++
{
	CData1 tmp = a;
	a.Clean();
	a.n = tmp.n + 1;
	a.m = new int[a.n+1];
	a.m[0] = 0;
	for(int i = 1; i < a.n+1; i++)
		a.m[i] = (tmp.m[i-1] * inverse(i))%P;
	return tmp;
}


CData1 operator--(CPoly &a)
{                         
	CData1 tmp = a;	
	if(a.n > 0)
	{			a.Clean();
		a.n = tmp.n - 1;
		a.m = new int[a.n+1];
		for(int i = 0; i < a.n+1; i++)
			a.m[i] = (tmp.m[i+1] * (i+1))%P;
	}
	else
		a.m[0] = 0;
	return a;
}
CData1 operator--(CPoly &a, int)
{
	CData1 tmp = a;	
	if(a.n > 0)
	{
		a.Clean();
		a.n = tmp.n - 1;
		a.m = new int[a.n+1];
		for(int i = 0; i < a.n+1; i++)
		a.m[i] = (tmp.m[i+1] * (i+1))%P;
	}
	else
		a.m[0] = 0;
	return tmp;
}                                 

ostream &operator<<(ostream &cout, const CPoly &a)
{
	for(int i = 0; i < a.n; i++)
		cout << a.m[i] << "*x^" << i << " + ";
	cout << a.m[a.n] << "*x^" << a.n << endl;
	return cout;
}
                                  
//-------------------------------------------------------------------
//для работы с полем вычетов
int gcdex(int a, int b, int & x, int & y)
{
	if (a == 0) 
	{
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcdex(b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

int inverse(int a)
{
    int x, y; 
	gcdex (a, P, x, y);	
	x = (x % P + P) % P;
	return x;
}
//-------------------------------------------------------------------
