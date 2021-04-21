#include "my.h"
//-------------------------------------------------------------------------------------
void read_data(const char * file, CList & points)//Считывание из файла
{
    double x, y;
    ifstream f(file);
	char open_bracket, comma, close_bracket;
    if (!(f.is_open()))  // проверка наличия файла с
        cout << "ERROR: no file " << file;
    else
    {
        while(f >> open_bracket >> x >> comma >> y >> close_bracket) // чтение из файла
        {   
			if(open_bracket == '(' && comma == ',' && close_bracket == ')')
			{
				points.AddAfter(Circle(x, y, 0., true));
				points.GoToNext();
			}
			else
			{
				cout << "bad input" << endl;
				break;
				points.Clean();
			}
			open_bracket = comma = close_bracket = '*';
		}
		if(open_bracket == '(' && (close_bracket != ')' || comma != ',' ))
		{
			cout << "bad input" << endl;
			points.Clean();
		}
		else if (open_bracket != '*')
		{
			cout << "bad input" << endl;
			points.Clean();
		}
	}
	f.close();
}
//-------------------------------------------------------------------------------------
void grow(CList & circles) //задача --- рост окружностей
{
	double delta = 0.001;
	while(true)
	{
		for(auto it = circles.begin(); it != circles.end(); ++it)
			if((*it).f)
				(*it).r += delta;
			
		for(auto it1 = circles.begin(); it1 != circles.end(); ++it1)
			for(auto it2 = circles.begin(); it2 != circles.end() && it2 != it1; ++it2)
				if(dist(*it1, *it2) <= (*it1).r + (*it2).r)
				{
					(*it1).f = false;
					(*it2).f = false;
				}
			
		bool fl = true;
		for(auto it = circles.begin(); it != circles.end(); ++it)
			if((*it).f)
				fl = false;
		if(fl)
			break;
	}
}
//-------------------------------------------------------------------------------------
//Для точек (окружностей)
int Circle:: operator==(Circle &b)
{
	return (fabs(x - b.x) < 0.00001) && (fabs(y - b.y) < 0.00001);
}

ostream &operator<<(ostream &cout, const Circle &p)
{
	cout << "(" << p.x << ", " << p.y << "), radius = " << p.r << endl;
	return cout;
}

double dist(Circle one, Circle two)
{
	return sqrt((one.x - two.x)*(one.x - two.x) + (one.y - two.y)*(one.y - two.y));
}

CList & CList::operator=(CList&b)//присваивание списков
{	
	if(this!=&b)
	{
		Clean();
		Circle c; 
		GoToBegin(); 
		for(b.GoToBegin(); b.GoToNext()==0;)
		{
			b.GetCur(c);
			AddAfter(c);
			GoToNext();
		}  
	}	
	return *this;
}	

CList:: CList( CList &b)
{
	
		Circle c; 
		GoToBegin(); 
		for(b.GoToBegin(); b.GoToNext()==0;)
		{
			b.GetCur(c);
			AddAfter(c);
			GoToNext();
		}  
}
