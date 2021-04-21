//Задача №8
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;
class Circle
{public:
	double x, y, r;
	bool f; // растёт ли окружность
	Circle(){x = 0.; y = 0.; r = 0.;  f = true;}
	Circle(double x, double y, double r, bool f){this->x = x; this->y = y; this->r = r; this->f = f;}
	int operator==(Circle &);
	friend ostream &operator<<(ostream &, const Circle &);
};


vector<Circle> read_data(const char *);
void grow(vector<Circle> &);
double dist(Circle, Circle);
