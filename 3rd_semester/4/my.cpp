#include"my.h"
//---------------------------------------------------------------------------------------
//Методы вершин дерева
PointTree::PointNode:: PointNode(Point p)//добавление точки
{
	this->p = p;
	this->radius = 0;
	this->n = n;
	this->lt = this->lb = this->rb = this->rt = nullptr;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PointTree::PointNode:: PointNode(Point center, double radius,  Point* points, int n)//добавление квадрата (поддерева)
{
	if(n == 0)
		return;
	this->p = center;
	this->n = n;
	this->radius = radius;
	//счётчики для каждого из 4-х квадратов, на которые поделится данный
	int j = 0, k = 0, l = 0, q = 0;
	//массивы точек в каждом квадрате
	Point *points_rt = new Point[n];
	Point *points_rb = new Point[n];
	Point *points_lt = new Point[n];
	Point *points_lb = new Point[n];
	for(int i = 0; i < n; i++)//разбиваем точки на четыре квадрата
	{
		if(((points[i].x - center.x) >= 0) && ((points[i].y - center.y) >= 0))//rt
		{
			if(is_in(points_rt, j, points[i]))//не добавили ли мы уже такую точку?
				(this->n)--;//не будем её считать
			else
			{
				points_rt[j] = points[i];//если нет, то добавляем
				j++;
			}
		}
		if(((points[i].x - center.x) >= 0) && ((points[i].y - center.y) < 0))//rb
		{
			if(is_in(points_rb, k, points[i]))//не добавили ли мы уже такую точку?
				(this->n)--;//не будем её считать
			else
			{
				points_rb[k] = points[i];//если нет, то добавляем
				k++;
			}
		}
		if(((points[i].x - center.x) < 0) && ((points[i].y - center.y) >= 0))//lt
		{
			if(is_in(points_lt, l, points[i]))//не добавили ли мы уже такую точку?
				(this->n)--;//не будем её считать
			else
			{
				points_lt[l] = points[i];//если нет, то добавляем
				l++;
			}
		}
		if(((points[i].x - center.x) < 0) && ((points[i].y - center.y) < 0))//lb
		{
			if(is_in(points_lb, q, points[i]))//не добавили ли мы уже такую точку?
				(this->n)--;//не будем её считать
			else
			{
				points_lb[q] = points[i];//если нет, то добавляем
				q++;
			}
		}
	}
	//запускаем создание новых квадратов из малых, если в них больше 1 точки
	if(j == 1)//1 точка в rt
	{
		PointNode *t = new PointNode(points_rt[0]);
		this->rt = t;//прикрепили точку
	}
	if(j > 1)
	{
		Point newcenter(center.x + radius/2, center.y + radius/2);
		//прикрепляем поддерево
		PointNode *t = new PointNode(newcenter, radius/2, points_rt, j);
		this->rt = t;
	}
	if(j == 0)
		this->rt = nullptr;
	
	if(k == 1)//1 точка в rb
	{
		PointNode *t = new PointNode(points_rb[0]);
		this->rb = t;//прикрепили точку
	}
	if(k > 1)
	{
		Point newcenter(center.x + radius/2, center.y - radius/2);
		//прикрепляем поддерево
		PointNode *t = new PointNode(newcenter, radius/2, points_rb, k);
		this->rb = t;
	}
	if(k == 0)
		this->rb = nullptr;
	
	if(l == 1)//1 точка в lt
	{
		PointNode *t = new PointNode(points_lt[0]);
		this->lt = t;//прикрепили точку
	}
	if(l > 1)
	{
		Point newcenter(center.x - radius/2, center.y + radius/2);
		//прикрепляем поддерево
		PointNode *t = new PointNode(newcenter, radius/2, points_lt, l);
		this->lt = t;
	}
	if(l == 0)
		this->lt = nullptr;
	
	if(q == 1)//1 точка в lb
	{
		PointNode *t = new PointNode(points_lb[0]);
		this->lb = t;//прикрепили точку
	}
	if(q > 1)
	{
		Point newcenter(center.x - radius/2, center.y - radius/2);
		//прикрепляем поддерево
		PointNode *t = new PointNode(newcenter, radius/2, points_lb, q);
		this->lb = t;
	}
	if(q == 0)
		this->lb = nullptr;

	
	
	delete[] points_rt;
	delete[] points_rb;
	delete[] points_lt;
	delete[] points_lb;//всё подчистили
	points_lb = points_rb = points_lt = points_rt = nullptr;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PointTree::PointNode:: PointNode(PointNode &b)
{
	this->p = b.p;
	this->radius = b.radius;
	this->n = b.n;
	if(b.rt)
		this->rt = new PointNode(*b.rt);
	else
		this->rt = nullptr;
	if(b.rb)
		this->rb = new PointNode(*b.rb);
	else
		this->rb = nullptr;
	if(b.lt)
		this->lt = new PointNode(*b.lt);
	else
		this->lt = nullptr;
	if(b.lb)
		this->lb = new PointNode(*b.lb);
	else
		this->lb = nullptr;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PointTree::PointNode & PointTree::PointNode:: operator=(PointNode &b)
{
	if(this == &b)
		return *this;
	delete rb;
	delete rt;
	delete lt;
	delete lb;
	this->p = b.p;
	this->radius = b.radius;
	this->n = b.n;
	if(b.rt)
		this->rt = new PointNode(*b.rt);
	else
		this->rt = nullptr;
	if(b.rb)
		this->rb = new PointNode(*b.rb);
	else
		this->rb = nullptr;
	if(b.lt)
		this->lt = new PointNode(*b.lt);
	else
		this->lt = nullptr;
	if(b.lb)
		this->lb = new PointNode(*b.lb);
	else
		this->lb = nullptr;
	return *this;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PointTree::PointNode:: ~PointNode()
{
	delete rt;//и тут подчистили
	delete rb;
	delete lt;
	delete lb;
	rt = lt = rb = lb = nullptr;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PointTree::PointNode:: Ins(Point new_p)
{
	n++;
	if((fabs(p.x - new_p.x) > radius) || (fabs(p.y - new_p.y) > radius)) 
	{
		cout << "ERROR" << endl;
		return;//если вдруг кто-то решит вставить точку вне исходного квадрата
	}
	if((new_p.x >= p.x) && (new_p.y >= p.y))//rt
	{
		if(rt == nullptr)//точки в этом квадрате ещё нет
		{
			PointNode *t = new PointNode(new_p);
			rt = t;//прикрепили точку
		}
		else
		{
			if(rt->radius > 0)//если уже висит поддерево, а не точка
				rt->Ins(new_p);//вставляем точку в это поддерево
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(p == new_p)
					return;
				else
				{
					//cоздаём и прикрепляем поддерево c двумя точками
					Point newcenter(p.x + radius/2, p.y + radius/2);
					Point points[2]; points[0] = rt->p; points[1] = new_p;
					delete rt;//не забыли удалить точку
					PointNode *t = new PointNode(newcenter, radius/2, points, 2);
					rt = t;
				}
			}
		}
	}
	if((new_p.x >= p.x) && (new_p.y < p.y))//rb
	{
		if(rb == nullptr)//точки в этом квадрате ещё нет
		{
			PointNode *t = new PointNode(new_p);
			rb = t;//прикрепили точку
		}
		else
		{
			if(rb->radius > 0)//если уже висит поддерево, а не точка
				rb->Ins(new_p);//вставляем точку в это поддерево
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(p == new_p)
					return;
				else
				{
					//cоздаём и прикрепляем поддерево c двумя точками
					Point newcenter(p.x + radius/2, p.y - radius/2);
					Point points[2]; points[0] = rb->p; points[1] = new_p;
					delete rb;//не забыли удалить точку
					PointNode *t = new PointNode(newcenter, radius/2, points, 2);
					rb = t;
				}
			}
		}
	}
	if((new_p.x < p.x) && (new_p.y >= p.y))//lt
	{
		if(lt == nullptr)//точки в этом квадрате ещё нет
		{
			PointNode *t = new PointNode(new_p);
			lt = t;//прикрепили точку
		}
		else
		{
			if(lt->radius > 0)//если уже висит поддерево, а не точка
				lt->Ins(new_p);//вставляем точку в это поддерево
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(p == new_p)
					return;
				else
				{
					//cоздаём и прикрепляем поддерево c двумя точками
					Point newcenter(p.x - radius/2, p.y + radius/2);
					Point points[2]; points[0] = lt->p; points[1] = new_p;
					delete lt;//не забыли удалить точку
					PointNode *t = new PointNode(newcenter, radius/2, points, 2);
					lt = t;
				}
			}
		}
	}
	if((new_p.x < p.x) && (new_p.y < p.y))//lb
	{
		if(lb == nullptr)//точки в этом квадрате ещё нет
		{
			PointNode *t = new PointNode(new_p);
			lb = t;//прикрепили точку
		}
		else
		{
			if(lb->radius > 0)//если уже висит поддерево, а не точка
				lb->Ins(new_p);//вставляем точку в это поддерево
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(p == new_p)
					return;
				else
				{
					//cоздаём и прикрепляем поддерево c двумя точками
					Point newcenter(p.x - radius/2, p.y - radius/2);
					Point points[2]; points[0] = lb->p; points[1] = new_p;
					delete lb;//не забыли удалить точку
					PointNode *t = new PointNode(newcenter, radius/2, points, 2);
					lb = t;
				}
			}
		}
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int PointTree::PointNode:: Del(Point del_p)
{
	if((del_p.x >= p.x) && (del_p.y >= p.y))//rt
	{
		if(rt == nullptr)//точки в этом квадрате нет
			return -1;
		else
		{
			if(rt->radius > 0)
			{//если висит поддерево, а не точка
				int f = rt->Del(del_p);//удаляем точку из этого поддерева
				if(f == 0)
				{
					n--;
					return 0;
				}
				return -1;
			}
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(rt->p == del_p)
				{
					n--;
					delete rt;
					rt = nullptr;
					return 0;
				}
				else
					return -1;
			}
		}
	}
	if((del_p.x >= p.x) && (del_p.y < p.y))//rb
	{
		if(rb == nullptr)//точки в этом квадрате нет
			return -1;
		else
		{
			if(rb->radius > 0)
			{//если висит поддерево, а не точка
				int f = rb->Del(del_p);//удаляем точку из этого поддерева
				if(f == 0)
				{
					n--;
					return 0;
				}
				return -1;
			}
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(rb->p == del_p)
				{
					n--;
					delete rb;
					rb = nullptr;
					return 0;
				}
				else
					return -1;
			}
		}
	}
	if((del_p.x < p.x) && (del_p.y >= p.y))//lt
	{
		if(lt == nullptr)//точки в этом квадрате нет
			return -1;
		else
		{
			if(lt->radius > 0)
			{//если висит поддерево, а не точка
				int f = lt->Del(del_p);//удаляем точку из этого поддерева
				if(f == 0)
				{
					n--;
					return 0;
				}
				return -1;
			}
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(lt->p == del_p)
				{
					n--;
					delete lt;
					lt = nullptr;
					return 0;
				}
				else
					return -1;
			}
		}
	}
	if((del_p.x < p.x) && (del_p.y < p.y))//lb
	{
		if(lb == nullptr)//точки в этом квадрате нет
			return -1;
		else
		{
			if(lb->radius > 0)
			{//если висит поддерево, а не точка
				int f = lb->Del(del_p);//удаляем точку из этого поддерева
				if(f == 0)
				{
					n--;
					return 0;
				}
				return -1;
			}
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(lb->p == del_p)
				{
					n--;
					delete lb;
					lb = nullptr;
					return 0;
				}
				else
					return -1;
			}
		}
	}
	return -2;//если вдруг кто-то решит удалить точку вне исходного квадрата
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int PointTree::PointNode:: Find(Point find_p)
{
	if((find_p.x >= p.x) && (find_p.y >= p.y))//rt
	{
		if(rt == nullptr)//никакой точки в этом квадрате нет
			return 0;
		else
		{
			if(rt->radius > 0)//если висит поддерево, а не точка
				return rt->Find(find_p);//ищем точку в этом поддереве
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(rt->p == find_p)
					return 1;//нашли
				else
					return 0;
			}
		}
	}
	if((find_p.x >= p.x) && (find_p.y < p.y))//rb
	{
		if(rb == nullptr)//никакой точки в этом квадрате нет
			return 0;
		else
		{
			if(rb->radius > 0)//если висит поддерево, а не точка
				return rb->Find(find_p);//ищем точку в этом поддереве
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(rb->p == find_p)
					return 1;//нашли
				else
					return 0;
			}
		}
	}
	if((find_p.x < p.x) && (find_p.y >= p.y))//lt
	{
		if(lt == nullptr)//никакой точки в этом квадрате нет
			return 0;
		else
		{
			if(lt->radius > 0)//если висит поддерево, а не точка
				return lt->Find(find_p);//ищем точку в этом поддереве
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(lt->p == find_p)
					return 1;//нашли
				else
					return 0;
			}
		}
	}
	if((find_p.x < p.x) && (find_p.y < p.y))//lb
	{
		if(lb == nullptr)//никакой точки в этом квадрате нет
			return 0;
		else
		{
			if(lb->radius > 0)//если висит поддерево, а не точка
				return lb->Find(find_p);//ищем точку в этом поддереве
			else //если висит всего лишь одна точка, а не поддерево
			{
				if(lb->p == find_p)
					return 1;//нашли
				else
					return 0;
			}
		}
	}
	return 0;//если точка вне исходного квадрата
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PointTree::PointNode:: Pr()
{
	if(radius > 0)
	{
		if(rt)
		{
			if(rt->radius > 0)
				rt->Pr();
			else
				cout << rt->p << endl;
		}
		if(rb)
		{
			if(rb->radius > 0)
				rb->Pr();
			else
				cout << rb->p << endl;
		}
		if(lt)
		{
			if(lt->radius > 0)
				lt->Pr();
			else
				cout << lt->p << endl;
		}	
		if(lb)
		{
			if(lb->radius > 0)
				lb->Pr();
			else
				cout << lb->p << endl;
		}
	}
	else
		cout << p << endl;
}

void PointTree::PointNode:: PrintNeighbours(Point center, Point angle_point)
{
	double delta_x = fabs(center.x - angle_point.x), delta_y = fabs(center.y - angle_point.y);
	if(delta_x <0.000001 || delta_y < 0.000001)//чтобы исключить вырожденные прямоугольники
		return;
	if(radius > 0)//пришли в поддерево
	{
		if(center.x + delta_x >= p.x)
		{
			if(center.y + delta_y >= p.y)
			{
				if(center.x - delta_x >= p.x)
				{
					if(center.y - delta_y >= p.y)
					{
						if(rt)
							rt->PrintNeighbours(center, Point(center.x + delta_x, center.y + delta_y));
					}
					else
					{
						if(rt)
							rt->PrintNeighbours(Point(center.x, (center.y + delta_y + p.y)/2), Point(center.x + delta_x, center.y + delta_y));
						if(rb)
							rb->PrintNeighbours(Point(center.x, (center.y - delta_y + p.y)/2), Point(center.x + delta_x, center.y - delta_y));
					}
				}
				else
				{
					if(center.y - delta_y >= p.y)
					{
						if(rt)
							rt->PrintNeighbours(Point((center.x + delta_x + p.x)/2, center.y), Point(center.x + delta_x, center.y + delta_y));
						if(lt)
							lt->PrintNeighbours(Point((center.x - delta_x + p.x)/2, center.y), Point(center.x - delta_x, center.y + delta_y));
					}
					else
					{
						if(rt)
							rt->PrintNeighbours(Point((center.x + delta_x + p.x)/2, (center.y + delta_y + p.y)/2), Point(center.x + delta_x, center.y + delta_y));
						if(rb)
							rb->PrintNeighbours(Point((center.x + delta_x + p.x)/2, (center.y - delta_y + p.y)/2), Point(center.x + delta_x, center.y - delta_y));
						if(lt)
							lt->PrintNeighbours(Point((center.x - delta_x + p.x)/2, (center.y + delta_y + p.y)/2), Point(center.x - delta_x, center.y + delta_y));
						if(lb)
							lb->PrintNeighbours(Point((center.x - delta_x + p.x)/2, (center.y - delta_y + p.y)/2), Point(center.x - delta_x, center.y - delta_y));
					}
				}
			}
			else
			{
				if(center.x - delta_x >= p.x)
				{
					if(rb)
						rb->PrintNeighbours(center, Point(center.x + delta_x, center.y - delta_y));
				}
				else
				{
					if(rb)
						rb->PrintNeighbours(Point((center.x + delta_x + p.x)/2, center.y), Point(center.x + delta_x, center.y + delta_y));
					if(lb)
						lb->PrintNeighbours(Point((center.x - delta_x + p.x)/2, center.y), Point(center.x - delta_x, center.y + delta_y));
				}
			}
		}	
		else
		{
			if(center.y + delta_y >= p.y)
			{
				if(center.y - delta_y >= p.y)
				{
					if(lt)
						lt->PrintNeighbours(center, Point(center.x - delta_x, center.y + delta_y));
				}
				else
				{
					if(lt)
						lt->PrintNeighbours(Point(center.x, (center.y + delta_y + p.y)/2), Point(center.x + delta_x, center.y + delta_y));
					if(lb)
						lb->PrintNeighbours(Point(center.x, (center.y - delta_y + p.y)/2), Point(center.x + delta_x, center.y - delta_y));
				}
			}
			else
			{
				if(lb)
					lb->PrintNeighbours(center, Point(center.x - delta_x, center.y - delta_y));
			}
		}
	}
	else//пришли в точку
	{
		if((fabs(center.x - p.x) <= delta_x) && (fabs(center.y - p.y) <= delta_y))
			cout << p << " ";
	}
}
//---------------------------------------------------------------------------------------
//методы дерева
Point PointTree:: Center()
{
	return root->p;
}

double PointTree:: Radius()
{
	return root->radius;
}

PointTree:: PointTree(Point center, double radius)
{
	Point *points = new Point[1];
	points[0] = Point(0,0);
	root = new PointNode(center, radius, points, 1); 
	delete[] points;
}

PointTree:: PointTree(Point *points, int n)
{
	if(n == 0)
		return;
	//создаеми исходный квадрат
	Point center(0,0);
	double radius = -1;
	for(int i = 0; i < n; i++)//первый центр --- среднее арифметическое
	{
		center.x += points[i].x/n;
		center.y += points[i].y/n;
	}
	for(int i = 0; i < n; i++)//радиус --- наибольшее удаление от центра
	{
		if(fabs(center.x - points[i].x) > radius)
			radius = fabs(center.x - points[i].x) + 1;//чуть больше, чтобы точка не лежала на границе 
		if(fabs(center.y - points[i].y) > radius)
			radius = fabs(center.y - points[i].y) + 1;
	}
	//Добавили исходный квадрат в корень
	root = new PointNode(center, radius, points, n); 
}

PointTree:: PointTree(PointTree &b)
{
	root = new PointNode(*b.root);
}

PointTree:: ~PointTree()
{
	if(root) 
		delete root;
}
PointTree & PointTree:: operator=(PointTree &b)
{
	if(this == &b)
		return *this;
	if(root)
	{	
		delete root;
		root = new PointNode(*b.root);
	}
	else
		root = new PointNode(*b.root);
	return *this;
}

void PointTree:: Ins(Point p)
{
	if(root)
		if(root->Find(p) == 0)//если такой точки нет
			root->Ins(p);
}

int PointTree:: Find(Point p)
{
	if(root) 
		return root->Find(p); 
	else return -5;
}

int PointTree:: Size()
{
	if(root) 
		return root->Size(); 
	else return -5;
}


void PointTree:: Pr()
{
	if(root)
	{
		cout<<"RIGHT TOP:"<<endl;
		if(root->rt)
			root->rt->Pr();
		cout<<"RIGHT BOTTOM:"<<endl;
		if(root->rb)
			root->rb->Pr();
		cout<<"LEFT TOP:"<<endl;
		if(root->lt)
			root->lt->Pr();
		cout<<"LEFT BOTTOM:"<<endl;
		if(root->lb)
			root->lb->Pr();
	}
}

int PointTree:: Del(Point p)
{
	if(root) 
		return root->Del(p);
	else return -5;
}

void PointTree:: PrintNeighbours(Point center, Point angle_point)
{
	if(root)
	{
		cout << "Neighbours of point " << center <<":" << endl;
		root->PrintNeighbours(center, angle_point);
		cout << endl;
	}
}
//-------------------------------------------------------------------------------------
//Считывание из файла
Point* read_data(FILE *in, int *n){
    Point *a = nullptr;
    char buf[128];
    int k = 0;
    *n = 1;
    while(fgets(buf, 128, in) != 0)
    {
        char *ptr;
        if((ptr = strchr(buf,'\n')) != NULL)
            *ptr = '\0';
        if(buf[0] != '\0')
        {
            k++;
            if(k == *n)
            {
                (*n) *= 2;
                a = (Point*)realloc(a, sizeof(Point) * (*n));
            }
            a[k-1] = get_point(buf);
        }
    }
    *n = k;
    return a;
}
Point get_point(char *buf)
{
	int i, k;
	double x, y;
	char sx[128], sy[128]; 
	for(int j = 0; j < 128; j++)
	{
		sx[j] = sy[j] = '0';
	}//чтобы valgrind не ругался на неинициализированность
	
	for(i = 1; buf[i] != ','; i++)
		sx[i-1] = buf[i];
	sx[i-1] = '\0';
	i++;
	k = i;
	for(; buf[i] != ')';i++)
		sy[i-k] = buf[i];
	sy[i-k] = '\0';
	x = atof(sx);//сделали из char double
	y = atof(sy);
	return Point(x,y);
}
//-------------------------------------------------------------------------------------
//Создание случайных точек 
Point * rand_points(int k)
{
	Point *points = new Point[k];
	cout << "rand_points: ";
	for(int i = 0; i < k; i++)
	{
		points[i] = Point(rand()%10,rand()%10);
		cout << points[i] << " ";
	}
	cout << endl;
	return points;
}
//-------------------------------------------------------------------------------------
//Для точек
int Point:: operator==(Point &b)
{
	return (fabs(x - b.x) < 0.00001) && (fabs(y - b.y) < 0.00001);
}

ostream &operator<<(ostream &cout, const Point &p)
{
	cout << "(" << p.x << ", " << p.y << ")";
	return cout;
}

int is_in(Point * points, int n, Point p)
{
	for(int i = 0; i < n; i++)
		if(points[i] == p)
			return 1;
	return 0;
}
