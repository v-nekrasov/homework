#include "my.h"
int main()
{
	
	PointTree t(Point(0,0), 5.);//создание пустого квадрата по центру и радиусу
	t.Ins(Point(0.1,0.2));
	t.Ins(Point(0.2,0.6));  
	t.Ins(Point(-0.2,-0.4));
	t.Ins(Point(0,0.4));

	t.Ins(Point(-4,4));
	cout << "size = " << t.Size() << endl;
	t.Pr();
	cout << endl;
	t.PrintNeighbours(Point(-4,4), Point(0.2, 0.1));

	PointTree d(Point(1, 0.2), 2);
	d.Ins(Point(0.4, 0.7));
	cout << "Other tree:" << endl;
	d = t;
t.Del(Point(0,0));
	d.Pr();
puts("++");
t.Pr();

//	return 0;
//считывание из файла
	int n; 
	FILE *in = fopen("1.txt", "r");
	Point *points = read_data(in, &n);//загрузка точек из файла
	fclose(in);
	cout << "----------file_points--------------" << endl;
//создание класса и работа с ним
	PointTree p(points, n);
	cout << "center = " << p.Center() << "; radius = " << p.Radius() << endl;
	cout << "size = " << p.Size() << endl;
	p.Pr();
	cout<<"------Ins-------"<<endl;
	p.Ins(Point(0.5,-0.5));//не предполагается, что можно вставлять точки вне исходного прямоугольника
	p.Ins(Point(0.1,0.2));
	p.Ins(Point(0.2,0.6));  
	p.Ins(Point(-0.2,-0.4));
	p.Ins(Point(-0.2,-0.4));
	cout << "size = " << p.Size() << endl;
	p.Pr();
	cout << "------Del-------" << endl;
	p.Del(Point(2,-1));//этой точки нет, она не удалится
	p.Del(Point(5,6.3));//а эта удалится
	cout << "size = " << p.Size() << endl;
	p.Pr();
	cout << "------Find-------" << endl;
	cout << "Is there point " << Point(3,4.222) << "? Answer = " << p.Find(Point(3,4.222)) << endl;
	cout << "Is there point " << Point(5, 6.3) << "? Answer = " << p.Find(Point(5, 6.3)) << endl;
//отчистка памяти
	free(points);
	points = nullptr;
	int k = 0;
	cout << "----------rand_points--------------" << endl;
//работа со случайными точками
	srand(time(NULL));
	k = 5; //количество случайных точек, size может быть меньше, если попадутся одинаковые точки
	points = rand_points(k);
	PointTree p2(points, k);
	cout << "center = " << p2.Center() << "; radius = " << p2.Radius() << endl;
	cout << "size = " << p2.Size() << endl;
	p2.Pr();
	cout<<"------Ins-------"<<endl;
	p2.Ins(Point(2,4));
	cout << "size = " << p2.Size() << endl;
	p2.Pr();
//отчистка памяти
	delete[] points;
	points = nullptr;
	return 0;
}
