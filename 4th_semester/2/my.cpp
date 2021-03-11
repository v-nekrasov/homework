#include "my.h"                                                        
//cчитывание из файла и создание объектов
int CPoly::read_data(const char *file, vector<CPoly*> &arr, vector<CFactory*> &f)
{
	ifstream in(file); string buf;
	if(in.is_open())
	{
		while(getline(in, buf))
		{
	    	int Type, x; string FileName; stringstream ss(buf); char c;
			if(!buf.empty())  
			{
				if((ss >> Type >> FileName) && (Type >= 0) && (Type <= 1)) 
				{
					CPoly *r = f[Type]->create();
					while(ss >> x)
					{
						if(x <= P && x >= 0)
							r->m.push_back(x);
						else
						{
							delete r;
							cout << "BAD DATA!" << endl;
							return 0;
						}
					}
					while(ss >> c && c == ' ');
					if(!ss.eof())
					{
							delete r;
							cout << "BAD DATA!" << endl;
							return 0;
					}
					r->FileName = FileName;
					arr.push_back(r);
				}
				else
				{
					cout << "BAD DATA" << endl;
					return 0;
				}     
			}       
		}
		return 1;
	}
	cout << "NO FILE" << endl;
	return 0;
}

//-------------------------------------------------------------------
//виртуальный вывод
void CData0:: output()
{	
	ofstream out(FileName.c_str(), ios::app); 	
	for(size_t i = 0; i < m.size()-1; i++)
		out << m[i] << "x^"<< i << " + ";
	out << m[m.size()-1] << "x^"<< m.size()-1 << endl << "------" << endl;		 
}
void CData1:: output()
{    
	ofstream out(FileName.c_str(), ios::app); 	
	for(size_t i = 0; i < m.size()-1; i++)
		out << m[i] << "x^"<< i << endl << "+" << endl ;
	out << m[m.size()-1] << "x^"<< m.size()-1 << endl << "------" << endl;		 
}
//-------------------------------------------------------------------
//Перегрузка операторов
CData1 operator+(const CPoly &a, const CPoly &c)
{              
	CData1 res;
	size_t na = a.m.size(), nc = c.m.size();
	if(na != nc)
	{
		if(na < nc)
		{		
			res.m.resize(nc);
			for(size_t i = 0; i < nc; i++)
				if(i < na)
					res.m[i] = (a.m[i] + c.m[i])%P;//res.m[i] = ((a.m[i]-c.m[i])%P > 0)?((a.m[i]-c.m[i])%P):(P+(a.m[i]-c.m[i])%P);
				else
					res.m[i] = (c.m[i])%P;//res.m[i] = (P-c.m[i])%P;			
		}
		else
		{
			res.m.resize(na);
			for(size_t i = 0; i < na; i++)
				if(i < nc)
					res.m[i] = (a.m[i]+c.m[i])%P;//((a.m[i]-c.m[i])%P > 0)?((a.m[i]-c.m[i])%P):(P+(a.m[i]-c.m[i])%P);

				else
					res.m[i] = (a.m[i])%P; //res.m[i] = (a.m[i])%P;
		}
	}
	else
	{
		res.m.resize(na);
		for(size_t i = 0; i < na; i++)
			res.m[i]=(a.m[i]+c.m[i])%P;
	}
	return res;
}

CData1 operator-(const CPoly &a, const CPoly &c)
{                           
	CData1 res;
	size_t na = a.m.size(), nc = c.m.size();
	if(na != nc)
	{
		if(na < nc)
		{		
			res.m.resize(nc);
			for(size_t i = 0; i < nc; i++)
				if(i < na)
					res.m[i] = ((a.m[i]-c.m[i])%P > 0)?((a.m[i]-c.m[i])%P):(P+(a.m[i]-c.m[i])%P);
				else
					res.m[i] = (P-c.m[i])%P;			
		}
		else
		{
			res.m.resize(na);
			for(size_t i = 0; i < na; i++)
				if(i < nc)
					res.m[i] = ((a.m[i]-c.m[i])%P > 0)?((a.m[i]-c.m[i])%P):(P+(a.m[i]-c.m[i])%P);

				else
					res.m[i]  = (a.m[i])%P;
		}
	}
	else
	{
		res.m.resize(na);
		for(size_t i = 0; i < na; i++)
			res.m[i] = ((a.m[i]-c.m[i])%P > 0)?((a.m[i]-c.m[i])%P):(P+(a.m[i]-c.m[i])%P);
	}
	return res;
}

CData1 operator++(CPoly &a)//++i
{                              
	CData1 tmp = a;
	a.m.push_back(0);	
	a.m[0] = 0;
	for(size_t i = 1; i < a.m.size(); i++)
		a.m[i] = (tmp.m[i-1] * inverse((int)i))%P;
	return a;
}

CData1 operator++(CPoly &a, int)//i++
{
	CData1 tmp = a;
	a.m.push_back(0);	
	a.m[0] = 0;
	for(size_t i = 1; i < a.m.size(); i++)
		a.m[i] = (tmp.m[i-1] * inverse((int)i))%P;
	return tmp;
}


CData1 operator--(CPoly &a)
{                         
	CData1 tmp = a;	
	if(a.m.size()>1)
	{			
		a.m.pop_back();
		for(size_t i = 0; i < a.m.size(); i++)
			a.m[i] = (tmp.m[i+1] * (int)(i+1))%P;
	}
	else
		a.m[0] = 0;
	return a;
}
CData1 operator--(CPoly &a, int)
{
	CData1 tmp = a;	
	if(a.m.size()>1)
	{			
		a.m.pop_back();
		for(size_t i = 0; i < a.m.size(); i++)
			a.m[i] = (tmp.m[i+1] * (int)(i+1))%P;
	}
	else
		a.m[0] = 0;
	return tmp;
}                                

ostream &operator<<(ostream &cout, const CPoly &a)
{
	for(size_t i = 0; i < a.m.size()-1; i++)
		cout << a.m[i] << "*x^" << i << " + ";
	cout << a.m[a.m.size()-1] << "*x^" << a.m.size()-1 << endl;
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
