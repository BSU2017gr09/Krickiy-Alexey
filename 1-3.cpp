//Разработать программу для работы с одним или несколькими одномерными массивами в heap, предусмотрев в ней:
 // - Размер массива N запрашивать у пользователя;
 // - выделение и контроль динамической памяти в отдельной функции, а не в main;
 // - организация циклов с использованием указателей, а не с помощью A[i];
 // - функции для инициализации, для ввода, для вывода массивов в heap;
 // - удаление динамической памяти после её использования желательно, но пока не обязательно в отдельной функции;
 // - одну или несколько функций для обработки массивов (для сортировки новый массив не создавать);
//3. Положительные элементы массива А(N) переставить в конец массива, сохраняя порядок следования. Отрицательные элементы расположить в порядке убывания. Дополнительный массив не использовать.

#include <cstdlib>
#include <iostream>
#include <ctime>
typedef int MAIN_TYPE;
typedef unsigned int SIZE_T;
const MAIN_TYPE MIN_VALUE=-9, MAX_VALUE=9;
void newArray(MAIN_TYPE *&pArr, const SIZE_T N) {
	try { 
		pArr = new MAIN_TYPE[N];
	}
	catch(...) {
		std::cout<<"Error.\n";
		exit(0);
	}
}
void deleteArray(MAIN_TYPE *&pArr) {
	delete []pArr;
}
void initArray(MAIN_TYPE *pArr, const SIZE_T N, const MAIN_TYPE MIN_VALUE = 0, const MAIN_TYPE MAX_VALUE = 10) {
	MAIN_TYPE *p = pArr;
	MAIN_TYPE mod;
	mod = (MAX_VALUE - MIN_VALUE+1);
	for(p=pArr; p<pArr+N; p++) *p=MAIN_TYPE(rand()%mod + MIN_VALUE); 
}
void inputArray(MAIN_TYPE *pArr, const SIZE_T N) {
	MAIN_TYPE *p = pArr;
	for(p=pArr; p<pArr+N; p++) std::cin>>(*p); 
}
void printArray(MAIN_TYPE *pArr, const SIZE_T N, const char DELIM = '\n') {
	MAIN_TYPE *p = pArr;
	for(p=pArr; p<pArr+N; p++) std::cout<<*p<<DELIM;
	std::cout<<'\n';
}
void sortArray(MAIN_TYPE *pLeftBoarder, MAIN_TYPE *pRightBoarder) {
	//Сортировка Хоара
	MAIN_TYPE *i = pLeftBoarder, *j = pRightBoarder;
	MAIN_TYPE x = *(pLeftBoarder+((pRightBoarder-pLeftBoarder)/2));
	do {
		while(*i<x) i++;
		while(*j>x) j--;
		if (i<=j) {
			if (i<j) {
				std::swap(*i,*j);
			}
			i++;
			j--;
		}
	} while (i<=j);
	if (i<pRightBoarder) sortArray(i,pRightBoarder);
	if (j>pLeftBoarder) sortArray(pLeftBoarder,j);
}
void reverseArray(MAIN_TYPE *pArr, SIZE_T N) {
	SIZE_T mid=N/2;
	MAIN_TYPE *p1 = pArr,*p2 = pArr+(N-1);
	for(p1=pArr; p1<pArr+mid; p1++,p2--) {
		std::swap(*p1,*p2);
	}
}
void replacePositiveElementsToEndAndSortNegative(MAIN_TYPE *pArr, const SIZE_T N) {
	//Если считать, что нули относятся к отрицательным элементам
	MAIN_TYPE *p=pArr+(N-1), *pNegative=pArr+(N-1);
	bool status = false;
	for (p=pArr+(N-1); p>=pArr; p--) {
		if (status) {
			if (*p>0) {
				std::swap(*pNegative,*p);
				p=pNegative;
				status=false;
			}
		} else {
			if ((*p)<=0) {
				pNegative=p;
				status=true;
			}
		}
	}
	for (p=pArr; p<pArr+N; p++) {
		if ((*p)>0) break;
	}
	if (p-pArr>1) {
		sortArray(pArr,p-1);
		reverseArray(pArr,SIZE_T(p-pArr));
	}
}
int main() {
	srand(SIZE_T(time(NULL)));
	SIZE_T N=1;
	MAIN_TYPE *A = 0;
	while(1) {
		std::cout<<"Write a size of array: ";
		std::cin>>N;
		if (!N) std::cout<<"Try again. ";
		else break; 
	}
	newArray(A,N);
	initArray(A,N,MIN_VALUE,MAX_VALUE);
	std::cout<<"Array: ";
	printArray(A,N,' ');
	replacePositiveElementsToEndAndSortNegative(A,N);
	std::cout<<"Result: ";
	printArray(A,N,' ');
	deleteArray(A);
	system("pause");
	return 0;
}