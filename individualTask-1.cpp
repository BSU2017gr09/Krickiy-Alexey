//Индивидуальное задание №1. Строки и указатели.
//38. Найти и удалить все слова в тексте, содержащие 1 слог. Вывести все такие слова на экран.
/*Слог — это один гласный звук или гласный звук в сочетании с согласным (или согласными) , которые произносятся одним толчком
выдыхаемого воздуха. В русском языке слогообразующим является гласный звук, поэтому в слове столько слогов, сколько в нём гласных: 
а-ри-я (3 слога) , ма-як (2 слога) , рейс (1 слог). Однако точно определить количество слогов в английском языке (по их правилам) очень сложная задача.*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <clocale>
const char* TaskInformation = "№38. Найти и удалить все слова в тексте, содержащие 1 слог. Вывести все такие слова на экран.\n*Слог — это один гласный звук или гласный звук в сочетании с согласным (или согласными) , которые произносятся одним толчком выдыхаемого воздуха.\nВ русском языке слогообразующим является гласный звук, поэтому в слове столько слогов, сколько в нём гласных: а-ри-я (3 слога) , ма-як (2 слога) , рейс (1 слог).  Однако точно определить количество слогов в английском языке (по их правилам) очень сложная задача.*";
typedef int MAIN_TYPE;
typedef unsigned int SIZE_TYPE;
typedef SIZE_TYPE fff(char *);
typedef fff *pfff;
const SIZE_TYPE NUM_OF_FUNCTIONS = 6;
SIZE_TYPE strLength = 1000;
void newStr(char *&str, const SIZE_TYPE N) {
	try { 
		str = new char[N];
		*str=0;
	}
	catch(...) {
		std::cout<<"Error.\n";
		exit(0);
	}
}
void deleteStr(char *&str) {
	delete []str;
}
SIZE_TYPE taskInfo(char *str) {
	std::cout<<"Текст условия задачи:\n"<<TaskInformation<<'\n';
	return 0;
}
SIZE_TYPE inputStr(char *str) {
	std::cout<<"Введите текст:\n";
	fflush(stdin);
	std::cin.getline(str, strLength);
	if (strlen(str)) {
		return 0;
	} else {
		return 1;
	}
}
bool isNumSyllables(char* word, SIZE_TYPE numOfSyllables=1) {
	char pat[] = "aeyuioAEYUIO";
	char *p1=word,*p2=word;
	SIZE_TYPE syllables = 0;
	while (1) {
		p1=p2+strcspn(p2, pat);
		if (syllables>numOfSyllables) return false;
		else {
			if (!(*p1)) break;
		}
		p2=p1+strspn(p1, pat);
		syllables+=(p2-p1);
	}
	if (syllables==numOfSyllables) return true;
	else return false;
}
SIZE_TYPE solveTask(char *str) {
	char pat[] = "., !?";
	char *pBegin = str+0, *pEnd = str;
	char *word;
	SIZE_TYPE numOfSyllables = 1;
	newStr(word,strLength);
	std::cout<<"Слова с "<<numOfSyllables<<" слогом(ами):";
	while(1) {
		pBegin = pEnd + strspn(pEnd, pat);
		pEnd = pBegin + strcspn(pBegin, pat);
		if (!(pEnd-pBegin)) break;
		strncpy(word,pBegin,(pEnd-pBegin));
		*(word+(pEnd-pBegin))='\0';
		if (isNumSyllables(word,numOfSyllables)) {
			std::cout<<' '<<word;
			strcpy(word,pEnd);
			strcpy(pBegin,word);
			pEnd=pBegin;
		}
	}
	std::cout<<'\n';
	std::cout<<"Итоговый текст: "<<str<<'\n';
	deleteStr(word);
	return 0;
}
SIZE_TYPE printStr(char *str) {
	if (*str) std::cout<<"Текст: "<<str<<'\n';
	else std::cout<<"Текст не введен.\n";
	return 0;
}
SIZE_TYPE writeMaxLength(char *str) {
	MAIN_TYPE userNum = 100;
	std::cout << "Введите максимальное количество символов в тексте: ";
	std::cin >> userNum;
	if (userNum>0) {
		strLength=(SIZE_TYPE)userNum+1;
		return 0;
	} else {
		std::cout << "Некорректный ввод. ";
		return 1;
	}
}
SIZE_TYPE exit(char *str) {
	exit(0);
	return 0;
}
void forEach(char *str, pfff pf) {
	SIZE_TYPE statusError = 0;
	statusError = pf(str);
	if (statusError) {
		std::cout << "Не выполнено.\n";
	} else {
		std::cout << "Выполнено.\n";
	}
}
void menu(char *str) {
	MAIN_TYPE userNum = 1;
	fff * Fmenu[NUM_OF_FUNCTIONS] = {taskInfo, inputStr, solveTask, printStr, writeMaxLength, exit};
	std::cout << "		Индивидуальное задание №1. Строки и указатели.\n";
	while (1) {
		std::cout << "\nМеню:\n";
		std::cout << "1) Показать условие задачи на экран\n";
		std::cout << "2) Ввести текст\n";
		std::cout << "3) Выполнить задачу над текстом\n";
		std::cout << "4) Вывести текст на экран\n";
		std::cout << "5) Уточнить максимальное количество символов в тексте (на данный момент: "<<strLength<<")\n";
		std::cout << "6) Завершить выполнение программы\n";
		std::cout << "Номер действия: ";
		std::cin >> userNum;
		if (userNum>=1 && userNum<=NUM_OF_FUNCTIONS) {
			forEach(str,Fmenu[userNum-1]);
		} else {
			std::cout << "Некорректный ввод.\n";
		}
	}
}
int main() {
	setlocale(LC_ALL, "ru");
	char *str;
	newStr(str,strLength);
	//str = "1a 34 ab ribbed";
	menu(str);
	deleteStr(str);
	system("pause");
	return 0;
}