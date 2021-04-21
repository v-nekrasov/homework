#include "my.h" 
int main()
{
	vector<Circle> circles;
	circles = read_data("1.txt");//загрузка точек из файла
	if(circles.size() > 1)
	{	
		grow(circles);//рост окружностей
		for(auto it = circles.begin(); it != circles.end(); ++it)
			cout << *it;
	}
	else if (circles.size() == 1)
		cout << "1 circle with inf radius" << endl;
	return 0;
}
