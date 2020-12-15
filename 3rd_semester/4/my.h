//Задача №18
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <math.h>
#include <vector>	
using namespace std;
class Point
{public:
	double x,y;
	Point(){x = 0.; y = 0.;}
	Point(double x, double y){this->x = x; this->y = y;}
	int operator==(Point &);
	friend ostream &operator<<(ostream &, const Point &);
};

class PointTree{//точки на плоскости, реализация с помощью дерева
public:
	class PointNode//одна вершина в дереве (поддерево)
	{	
		Point p;
		double radius;
		int n;//количество вершин в этом поддереве
		PointNode *lt, *lb, *rt, *rb; //left-top, left-bottom, right-top, right-bottom
	public:
		PointNode(){lb = lt = rt = rb = nullptr; n = 0;}
		PointNode(Point, double, Point*, int);
		PointNode(Point);
		PointNode(PointNode &);
		~PointNode();
		PointNode & operator=(PointNode &);
		int Size(){return n;};
		void Ins(Point);
		int Del(Point);
		int Find(Point);
		void Pr();
		void PrintNeighbours(Point, Point);//печатает все точки, прицепленные к this
		friend class PointTree;
	};
private: 
	PointNode *root;
public://методы для дерева
	PointTree(){root = nullptr;}
	PointTree(Point*, int);
	PointTree(Point, double);//пустой квадрат с центром и радиусом
	PointTree(PointTree &);
	~PointTree();
	PointTree & operator=(PointTree &);
	int Size();
	Point Center();
	double Radius();
	void Pr();
	void Ins(Point);
	int Del(Point);
	int Find(Point);
	void PrintNeighbours(Point, Point);
};

Point get_point(char *);
Point* read_data(FILE *, int *);
Point* rand_points(int);
int is_in(Point *, int, Point);
