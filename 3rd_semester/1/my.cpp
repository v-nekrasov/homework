#include"my.h"

CMatrix::CMatrix()
{
	for(int i=0; i<n; i++) 
		for(int j=0; j<n; j++) 
			m[i][j]=rand()%2;
}
CMatrix CMatrix::operator+(const CMatrix &b)
{ // будем использовать метод Гаусса
	CMatrix r; int n=r.size(),i,j,k; int tmp[2*N][N];
	for(i=0; i<n; i++)//копируем в tmp две матрицы --- получаем систему пересечения (приписали вторую систему снизу) 
		for(j=0; j<n; j++) 
	    	tmp[i][j]=m[i][j];
	for(i=0; i<n; i++) 
		for(j=0; j<n; j++) 
	    	tmp[i+n][j]=b.m[i][j];

	/*for(i=0; i<2*n; i++)
	{
		cout<<"|> ";
		for(j=0; j<n; j++)
			cout<<tmp[i][j]<<" ";
		cout<<"<|"<<endl;
	} */ //если понадобится отладочная печать --- печатается большая система пересечения перед стартом метода Гаусса
	/*далее --- метод Гаусса*/
	k=0;//в k-ую строку r будем записывать
	for(j=0; j<n; j++)//идём по столбцам
	{	
		 for(i=0; i<2*n; i++)
			if(tmp[i][j]==1) //встретили первый ненулевой эл-т в столбце
			{	
				for(int l=0; l<n; l++)//берем эту строку в результат
					r.m[k][l]=tmp[i][l];
				k++;
				for(int p=i+1; p<2*n; p++)//обнуляем столбец
					if(tmp[p][j]==1)
					{
						for(int l=0; l<n; l++)//вычитаем i-ую строку из p-ой
							tmp[p][l]=abs(tmp[p][l]-tmp[i][l]);		
					}
				for(int l=0; l<n; l++)//"стираем" строку --- больше её использовать не будем
					tmp[i][l]=2;
				break;	
			}
	}
	while(k<n)
	{
		for(int l=0; l<n; l++)//возможно, дописали нулевые строки
			r.m[k][l]=0;
		k++;	
	}

	/*for(i=0; i<2*n; i++)
	{
		cout<<"<| ";
		for(j=0; j<n; j++)
			cout<<tmp[i][j]<<" ";
		cout<<"|>"<<endl;
	}
	cout<<endl;*///если понадобится отладочная печать --- печатается большая система пересечения после метода Гаусса
	return r;
}

ostream &operator<<(ostream &cout, const CMatrix &a)
{
	for(int i=0; i<a.size(); i++)
	{
		cout<<"| ";
		for(int j=0; j<a.size(); j++)
			cout<<a.m[i][j]<<" ";
		cout<<"|"<<endl;
	}
	return cout;
}