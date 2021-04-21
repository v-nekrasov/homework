#include "my.h"
//-------------------------------------------------------------------------------------
vector<Circle> read_data(const char * file)//Считывание из файла
{
    double x, y;
	vector<Circle> points;
    ifstream f(file);
	char open_bracket, comma, close_bracket;
    if (!(f.is_open()))  // проверка наличия файла с
        cout << "ERROR: no file " << file;
    else
    {
        while(f >> open_bracket >> x >> comma >> y >> close_bracket) // чтение из файла
        {   
			if(open_bracket == '(' && comma == ',' && close_bracket == ')')
				points.push_back(Circle(x, y, 0., true));
			else
			{
				cout << "bad input" << endl;
				break;
				points.clear();
			}
			open_bracket = comma = close_bracket = '*';
		}
		if(open_bracket == '(' && (close_bracket != ')' || comma != ',' ))
		{
			cout << "bad input" << endl;
			points.clear();
		}
		else if (open_bracket != '*')
		{
			cout << "bad input" << endl;
			points.clear();
		}
	}
	f.close();
    return points;
}
//-------------------------------------------------------------------------------------
void grow(vector<Circle> & circles) //задача --- рост окружностей
{
	double delta = 0.001;
	while(true)
	{
		for(size_t i = 0; i < circles.size(); ++i)
			if(circles[i].f)
				circles[i].r += delta;
			
		for(size_t i = 0; i < circles.size(); ++i)
			for(size_t j = 0; j < circles.size() && j != i; ++j)
				if(dist(circles[i], circles[j]) <= circles[i].r + circles[j].r)
				{
					circles[i].f = false;
					circles[j].f = false;
				}
			
		bool fl = true;
		for(size_t i = 0; i < circles.size(); ++i)
			if(circles[i].f)
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
