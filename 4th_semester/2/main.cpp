#include "my.h"
int main(void)
{
	vector<CFactory *> f = {new CFactoryCData0(), new CFactoryCData1()};
	vector<CPoly *> arr;
	CData0 sum0; CData1 sum1;

//считывание данных из файла
	if(CPoly::read_data("input.txt", arr, f))	
    {      
	//сумма всех многочленов из файла	
		for(size_t i = 0; i < arr.size(); i++)
		{
			sum0 = sum0 + *(arr[i]);
			sum1 = sum1 + *(arr[i]);
		}
		sum0.FileName = "out_sum.txt";
		sum1.FileName = "out_sum.txt";
		sum0.output(); //сумма напечатется в файл out_sum.txt в строку
		sum1.output(); //сумма напечатается в столбец

	//тест на инкремент и декремент   
		cout << "INTEGRATE" << endl;
		cout << (*(arr[4]))++ << endl;  //выводится на экран исходный 4-ый многочлен, потом интегрируется
		cout << ++(*(arr[4])) << endl;  //выводится на экран проинтегрированный четвертый многочлен (уже второй раз)
		cout << "----------" << endl;
		cout << "DIFFERENTIATE" << endl;	
		cout << (*(arr[5]))-- << endl;
		cout << --(*(arr[5])) << endl;
		cout << "----------" << endl;        

	//тест на сложение и вычитание
		*arr[0] = *arr[1] + *arr[2] + CData1(15);
		*arr[3] = *arr[1] - *arr[2] - *arr[3];    

	//виртуальный вывод 
		for(size_t i = 0; i < arr.size(); i++)
			arr[i]->output();

	//циклический сдвиг
		CData1 r(2);
		r = *(arr[0]);    
		for(size_t i = 0; i < arr.size()-1; i++)
		{	
			*arr[i]=*arr[i+1];
			arr[i]->FileName = "out_move.txt";
		}
		arr[arr.size()-1]->FileName = "out_move.txt";
		*(arr[arr.size()-1]) = r; 
	//Указатели в массиве не изменили своих значений и типов, а объекты, 
	//на который они указывают, циклически сдвинулись вверх на 1 позицию. 
	//Теперь вывод не соответствует требуемому во входном файле, поэтому выводим результат в отдельный файл
		for(size_t i = 0; i < arr.size(); i++)
			arr[i]->output();
	}
//освобождение памяти
	for(size_t i = 0; i < arr.size(); i++)
	{
		delete arr[i];
		arr[i] = NULL;
	} 
	delete f[0];
	delete f[1];
	f[0]=f[1]=NULL;
	return 0;
}   
