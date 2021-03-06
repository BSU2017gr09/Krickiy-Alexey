﻿//В массиве размера N, заполненного случ.числами от 0 до 10, подсчитать количество элементов, встречающихся более одного раза.
//(Размер массива N запрашивать у пользователя; выделение и контроль динамической памяти прямо в main; в зависимости от задания создать одну или несколько функций для обработки массивов, которые передавать туда через указатели; •	организация циклов с использованием указателей, а не с помощью A[i])
#include <iostream>
#include <ctime>
typedef int MAIN_TYPE;//целый
typedef unsigned int SIZE_T;
const MAIN_TYPE MIN_VALUE=0, MAX_VALUE=10;
void initArray(MAIN_TYPE *pArr, const SIZE_T N, const MAIN_TYPE MIN_VALUE = 0, const MAIN_TYPE MAX_VALUE = 10) {
	std::cout<<"Initialisation array.\n";
	MAIN_TYPE *p = pArr;
	MAIN_TYPE mod;
	mod = (MAX_VALUE - MIN_VALUE+1);
	for(p=pArr; p<pArr+N; p++) *p=MAIN_TYPE(rand()%mod + MIN_VALUE); 
}
void inputSize(SIZE_T *pNumber) {//Глупо иметь такую функцию. Чем она лучше, чем 2 строки в main???
	std::cout<<"Write a size: ";
	std::cin>>*pNumber;
}
void printArray(MAIN_TYPE *pArr, const SIZE_T N, const char DELIM = '\n') {
	std::cout<<"Array:"<<DELIM;
	MAIN_TYPE *p = pArr;
	for(p=pArr; p<pArr+N; p++) std::cout<<*p<<DELIM; 
	std::cout<<'\n';
}
SIZE_T numOfRepeatElemOfArr(MAIN_TYPE *pArr, const SIZE_T N) {
	SIZE_T numOfRepeatElements = 0;
	const SIZE_T SIZE_FLAGS_ARR=(SIZE_T)(MAX_VALUE-MIN_VALUE+1);
	char flags[SIZE_FLAGS_ARR] = {};
	MAIN_TYPE *p = pArr;//зачем? Мы же pArr имеем локально! Ну, да ладно...
	char *pchar = flags;
	for(p=pArr; p<pArr+N; p++) {
		if (*(flags+(*p-MIN_VALUE))<2) (*(flags+(*p-MIN_VALUE)))++; // условие неочевидное. Проверяешь, ведь на самом деле другое!!!
	}
	for(pchar=flags; pchar<flags+SIZE_FLAGS_ARR; pchar++) {
		if (*pchar > 1) numOfRepeatElements++;
	}
	std::cout<<"Number of elements that occur more than once in the array: "<<numOfRepeatElements<<'\n';//печать лишняя!!! Венрнул? там и печатай если надо
	return numOfRepeatElements;
}
int main() {
	srand(SIZE_T(time(NULL)));
	SIZE_T N = 0;
	SIZE_T answer = 0;
	inputSize(&N);
	MAIN_TYPE *pArray;
	try { 
		pArray = new MAIN_TYPE[N];
	}
	catch(...) {
		std::cout<<"Error.\n";
		exit(0);
	}
	initArray(pArray,N,MIN_VALUE,MAX_VALUE);
	printArray(pArray,N,' ');
	answer=numOfRepeatElemOfArr(pArray,N);
	delete []pArray;
	system("pause");
	return 0;
}
