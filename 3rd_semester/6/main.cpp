#include "my.h" 
int main()
{
	CList circles;
	read_data("1.txt", circles);//загрузка точек из файла
	if(circles.Length() > 1)
	{	
		grow(circles);//рост окружностей
		for(auto it = circles.begin(); it != circles.end(); ++it)
			cout << *it;
	}
	else if (circles.Length() == 1)
		cout << "1 circle with inf radius" << endl;
	return 0;
}
