﻿//Задание_8_курс_1_2017 КЛАССЫ. ОБЪЕКТЫ. Задача 2.
//№2. Определить объект, содержащую информацию о студенте факультета с полями  ФИО, курс, группа, оценки в сессию (сами решите в текущую, или вообще все), размер стипендии. Создать массив объектов. Разработать функции:
//a) определения студентов, сдавших сессию на  ”отлично”, на  ”хорошо” и ”отлично”, получивших удовлетворительные оценки, получивших неудовлетворительные оценки;
//b) определения количества студентов, получивших неудовлетворительные оценки, для каждой группы и каждого курса;
//c) для каждого студента назначить размер стипендии, выбрав самостоятельно какой-нибудь критерий;
//d) сортировки массива в порядке убывания среднего балла;
//e) сортировки массива по курсам, внутри курса – по полученной стипендии.
//f) Для каждого курса вывести список отличников в алфавитном порядке и долю (процент) их от общего числа отличников.
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <clocale>
#include <cstring>
#include <fstream>
#include <ctime>
const char* TaskInformation = "№2. Определить объект, содержащую информацию о студенте факультета с полями  ФИО, курс, группа, оценки в сессию (сами решите в текущую, или вообще все), размер стипендии. Создать массив объектов. Разработать функции:\n a) определения студентов, сдавших сессию на  ”отлично”, на  ”хорошо” и ”отлично”, получивших удовлетворительные оценки, получивших неудовлетворительные оценки;\n b) определения количества студентов, получивших неудовлетворительные оценки, для каждой группы и каждого курса;\n c) для каждого студента назначить размер стипендии, выбрав самостоятельно какой-нибудь критерий;	\n d) сортировки массива  в порядке убывания среднего балла;\n e) сортировки массива по курсам, внутри курса – по полученной стипендии.\n f) Для каждого курса вывести список отличников в алфавитном порядке и долю (процент) их от общего числа отличников.\n";
typedef float MAIN_TYPE;
typedef unsigned int SIZE_TYPE;
const SIZE_TYPE NUM_OF_FUNCTIONS = 14;
const char* NO_CORRECT_INPUT = "Некорректный ввод, попробуйте еще раз.";
const char* ERROR_MESSAGE = "Ошибка.\n";
const char* CURRENCY = "$";
char FILE_NAME[]="d:\\students-list.bd";
const SIZE_TYPE MAX_N = 1000;
const size_t MAX_LENGTH_WORD = 30;
const size_t MAX_NUM_OF_MARKS = 5;
const size_t MIN_NUM_OF_MARKS = 3;
const size_t MAX_MARK = 10;
const size_t MIN_MARK = 1;
const size_t VARIATION = 3;//разброс отметок у студента
const size_t MAX_COURSE = 5;
const size_t MIN_COURSE = 1;
const size_t NUM_OF_GROUPS = 9;
using namespace std;
class Student
{
private:
	char* surname;
	char* name;
	char* patronymic;
	char course;
	char group;
	char* marks;//код каждого символа соответсвует ("отметке"+1), т.е. здесь 2 - это "кол"
	float scholarship;
	int copystr(char*& copyto,const char* copyfrom, const size_t MAX_LEN=0) {
		if (copyto==copyfrom) return 0;
		if (copyfrom==nullptr) { 
			if (copyto!=nullptr) {
				delete[] copyto;
				copyto=nullptr;
			}
			return 0;
		}
		size_t len=0;
		char *tmp = nullptr;
		len=strlen(copyfrom);
		if (MAX_LEN && len>MAX_LEN) len=MAX_LEN;//если размер копируемой строки превышает максимально допустимый - копируется сколько можно символов
		try { tmp = new char[len+1]; }
		catch(...) { return 1; }
		strncpy(tmp,copyfrom,len);
		tmp[len]='\0';
		if (copyto!=nullptr) delete[] copyto;
		copyto = tmp;
		return 0;
	}
public:
	Student():
		surname(nullptr),
		name(nullptr),
		patronymic(nullptr),
		course(0),
		group(0),
		marks(nullptr),
		scholarship(0)//cчитается, что сначала стипендия не назначена
	{};
	Student(char* mysurname,
		char* myname=nullptr,
		char* mypatronymic=nullptr,
		char mycourse=0,
		char mygroup=0,
		char* mymarks=nullptr,
		float myscholarship=0
		):
		surname(nullptr),
		name(nullptr),
		patronymic(nullptr),
		course(mycourse),
		group(mygroup),
		marks(nullptr),
		scholarship(myscholarship)
	{
		if (setsurname(mysurname)) { /*cout<<ERROR_MESSAGE;*/ }//без exit() или исключений
		if (setname(myname)) { /*cout<<ERROR_MESSAGE;*/ }
		if (setpatronymic(mypatronymic)) { /*cout<<ERROR_MESSAGE;*/ }
		if (setmarks(mymarks)) { /*cout<<ERROR_MESSAGE;*/ }
		if (setcourse(mycourse)) { /*cout<<ERROR_MESSAGE;*/ }
		if (setgroup(mygroup)) { /*cout<<ERROR_MESSAGE;*/ }
		if (setscholarship(myscholarship)) { /*cout<<ERROR_MESSAGE;*/ }
	};
	Student(const Student &other):
		surname(nullptr),
		name(nullptr),
		patronymic(nullptr),
		course(other.course),
		group(other.group),
		marks(nullptr),
		scholarship(other.scholarship)
	{
		if (setsurname(other.surname)) { /*cout<<ERROR_MESSAGE;*/ }//без exit() или исключений
		if (setname(other.name)) { /*cout<<ERROR_MESSAGE;*/ }
		if (setpatronymic(other.patronymic)) { /*cout<<ERROR_MESSAGE;*/ }
		if (setmarks(other.marks)) { /*cout<<ERROR_MESSAGE;*/ }
	};
	~Student() {
		if (name!=nullptr) delete[] name;
		if (surname!=nullptr) delete[] surname;
		if (patronymic!=nullptr) delete[] patronymic;
		if (marks!=nullptr) delete[] marks;
	};
	friend void swap(Student& first, Student& second) {
		std::swap(first.surname, second.surname);
		std::swap(first.name, second.name);
		std::swap(first.patronymic, second.patronymic);
		std::swap(first.marks, second.marks);
		std::swap(first.course, second.course);
		std::swap(first.group, second.group);
		std::swap(first.scholarship, second.scholarship);
	};
	void swap(Student& other) {
		std::swap(surname, other.surname);
		std::swap(name, other.name);
		std::swap(patronymic, other.patronymic);
		std::swap(marks, other.marks);
		std::swap(course, other.course);
		std::swap(group, other.group);
		std::swap(scholarship, other.scholarship);
	};
	Student& operator=(const Student &other) {
		Student tmp(other);
		swap(tmp);
		return (*this);
	};
	Student& operator=(Student &&other) {
		if (this==&other) return *this;
		surname=other.surname;
		name=other.name;
		patronymic=other.patronymic;
		course=other.course;
		group=other.group;
		marks=other.marks;
		scholarship=other.scholarship;
		other.setname(nullptr);
		other.surname=nullptr;
		other.patronymic=nullptr;
		other.marks=nullptr;
		return (*this);
	};
	friend ostream& operator<<(ostream &myStream, Student &tmp) {//строка данных
		if (tmp.surname==nullptr) cout<<"не указана"<<' ';
		else cout<<tmp.surname<<' ';
		if (tmp.name==nullptr) cout<<"не указана"<<' ';
		else cout<<tmp.name<<' ';
		if (tmp.patronymic==nullptr) cout<<"не указано"<<"; ";
		else cout<<tmp.patronymic<<"; ";
		cout<<int(tmp.course)<<"; ";
		cout<<int(tmp.group)<<"; ";
		if (tmp.marks==nullptr || !strlen(tmp.marks)) cout<<"не указаны; ";
		else {
			char* p=tmp.marks;
			cout<<int(*p)-1;//по крайней мере одна отметка будет после проверки верхнего условия
			p++;
			while(*p) {
				cout<<" "<<int(*p)-1;
				p++;
			}
			cout<<"; ";
		}
		cout<<tmp.scholarship<<CURRENCY<<endl;
		return myStream;
	};
	friend istream& operator>>(istream &myStream, Student &tmp) {
		char tmpWord[MAX_LENGTH_WORD+1];
		short int *arrOfMarks;
		int mytmp=0;
		int N=0;
		//fflush(stdin); так плохо. UB!!!!!!!!!!!!!!!!!!!!!
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); //так вот рекомендуют
		cin.getline(tmpWord, MAX_LENGTH_WORD);
		//if (tmp.setsurname(tmpWord)) cout<<NO_CORRECT_INPUT<<endl;
		
		fflush(stdin);
		cin.getline(tmpWord, MAX_LENGTH_WORD);
		//if (tmp.setname(tmpWord)) cout<<NO_CORRECT_INPUT<<endl;

		fflush(stdin);
		cin.getline(tmpWord, MAX_LENGTH_WORD);
		//if (tmp.setpatronymic(tmpWord)) cout<<NO_CORRECT_INPUT<<endl;

		cin>>mytmp;
		//if (tmp.setcourse(mytmp)) cout<<NO_CORRECT_INPUT<<endl;

		cin>>mytmp;
		//if (tmp.setgroup(mytmp)) cout<<NO_CORRECT_INPUT<<endl;

		cin>>mytmp;
		if (mytmp>=0) {
			N=mytmp;
			try {
				arrOfMarks=new short int[N];
			}
			catch(...) {
				cout<<ERROR_MESSAGE;
				exit(0);
			}
			for (int i=0; i<N; i++) {
				cin>>mytmp;
				arrOfMarks[i]=mytmp;
			}
			//if (tmp.setmarks(arrOfMarks,N)) cout<<NO_CORRECT_INPUT<<endl;
			delete []arrOfMarks;
		} //else cout<<NO_CORRECT_INPUT<<endl;
		tmp.setscholarship();
		return myStream;
	};
	int setsurname(const char* mysurname) {
		return copystr(surname,mysurname,MAX_LENGTH_WORD);//на всякий случай возвращает код ошибки, но в любом случае присваевает сколько можно символов
	};
	int setname(const char* myname) {
		return copystr(name,myname,MAX_LENGTH_WORD);
	};
	int setpatronymic(const char* mypatronymic) {
		return copystr(patronymic,mypatronymic,MAX_LENGTH_WORD);
	};
	int setcourse(int mycourse) {
		if (mycourse<MIN_COURSE) { mycourse=(char)MIN_COURSE; return 1; }
		if (mycourse>MAX_COURSE) { mycourse=(char)MAX_COURSE; return 1; }
		course=char(mycourse);
		return 0;
	};
	int setgroup(int mygroup) {
		if (mygroup<1) { mygroup=(char)1; return 1; }
		if (mygroup>NUM_OF_GROUPS) { mygroup=(char)NUM_OF_GROUPS; return 1; }
		group=char(group);
		return 0;
	};
	int setmarks(const char* mymarks) {
		return copystr(marks,mymarks,MAX_NUM_OF_MARKS);
	};
	int setmarks(short int* mymarks,const int N) {
		if (N<0 || N>MAX_NUM_OF_MARKS) return 1;
		size_t i=0;
		for (i=0; i<size_t(N); i++) {//сначала проверка корректности всех отметок, а потом копирование, чтобы не портить данные объекта при неправильном вводе
			if (mymarks[i]<MIN_MARK || mymarks[i]>MAX_MARK) return 1;
		}
		char *tmp = nullptr;
		try { tmp = new char[N+1]; }
		catch(...) { return 1; };
		if (marks!=nullptr) delete[] marks;
		marks = tmp;
		for (i=0; i<size_t(N); i++) {
			marks[i]=char(mymarks[i]+1);
		}
		marks[N]=0;
		return 0;
	};
	float getmiddleMark() {
		if (marks==nullptr || !strlen(marks)) return 0;
		float sumMarks=0;
		size_t i=0;
		while(marks[i]) {
			sumMarks+=float(int(marks[i])-1);
			i++;
		}
		if (i) return sumMarks/float(i);
		else return 0;
	};
	bool isHonoursStudy() {//”отлично” - пусть это когда нет отметок ниже 9
		if (marks==nullptr || !strlen(marks)) return false;
		char* p=marks;
		while(*p) {
			if (int(*p)-1<9) return false;
			p++;
		}
		return true;
	};
	bool isGoodStudy() {//”хорошо” - пусть это когда нет отметок ниже 8 (в том числе и отличники)
		if (marks==nullptr || !strlen(marks)) return false;
		char* p=marks;
		while(*p) {
			if (int(*p)-1<8) return false;
			p++;
		}
		return true;
	};
	bool isBadStudy() {//"получивших неудовлетворительные оценки" - пусть это когда хотя бы одна отметка неудовлетворительная
		if (marks==nullptr || !strlen(marks)) return false;
		char* p=marks;
		while(*p) {
			if (int(*p)-1<4) return true;
			p++;
		}
		return false;
	};
	bool isNormalStudy() {//"получивших удовлетворительные оценки" - пусть это когда не ”хорошо” и не "неудовлетворительно"
		if (!isBadStudy() && !isGoodStudy()) return true;
		else return false;
	};
	int setscholarship(float myscholarship) {
		if (myscholarship<0) return 1;
		scholarship=myscholarship;
		return 0;
	};
	int setscholarship() {//пункт (с)
		float middlemark=0;
		middlemark=getmiddleMark();
		if (middlemark<5) scholarship=0;
		else 
			if (middlemark<6) scholarship=100;
			else 
				if (middlemark<7) scholarship=200;
				else 
					if (middlemark<8) scholarship=300;
					else 
						if (middlemark<9) scholarship=400;
						else
							if (middlemark<10) scholarship=1000;
							else scholarship=5000;
		return 0;
	};
	char* getname() {
		return name;
	};
	char* getsurname() {
		return surname;
	};
	char* getpatronymic() {
		return patronymic;
	};
	char getgroup() {
		return group;
	};
	char getcourse() {
		return course;
	};
	float getscholarship() {
		return scholarship;
	};
	void input() {
		char tmpWord[MAX_LENGTH_WORD+1];
		short int *arrOfMarks;
		int mytmp=0;
		int N=0;
		while(1) {
			cout<<"Введите фамилию: ";
			fflush(stdin);
			cin.getline(tmpWord, MAX_LENGTH_WORD);
			if (setsurname(tmpWord)) cout<<NO_CORRECT_INPUT<<endl;
			else break;
		}
		while(1) {
			cout<<"Введите имя: ";
			fflush(stdin);
			cin.getline(tmpWord, MAX_LENGTH_WORD);
			if (setname(tmpWord)) cout<<NO_CORRECT_INPUT<<endl;
			else break;
		}
		while(1) {
			cout<<"Введите отчество: ";
			fflush(stdin);
			cin.getline(tmpWord, MAX_LENGTH_WORD);
			if (setpatronymic(tmpWord)) cout<<NO_CORRECT_INPUT<<endl;
			else break;
		}
		while(1) {
			cout<<"Введите курс: ";
			cin>>mytmp;
			if (setcourse(mytmp)) cout<<NO_CORRECT_INPUT<<endl;
			else break;
		}
		while(1) {
			cout<<"Введите номер группы: ";
			cin>>mytmp;
			if (setgroup(mytmp)) cout<<NO_CORRECT_INPUT<<endl;
			else break;
		}
		while(1) {
			cout<<"Введите количество экзаменов за сессию: ";
			cin>>mytmp;
			if (mytmp>=0) {
				N=mytmp;
				try {
					arrOfMarks=new short int[N];
				}
				catch(...) {
					cout<<ERROR_MESSAGE;
					exit(0);
				}
				cout<<"Введите отметки за экзамены в сессию: ";
				for (int i=0; i<N; i++) {
					cin>>mytmp;
					arrOfMarks[i]=mytmp;
				}
				if (setmarks(arrOfMarks,N)) {
					cout<<NO_CORRECT_INPUT<<endl;
					delete []arrOfMarks;
				} else {
					delete []arrOfMarks;
					break;
				}
			} else cout<<NO_CORRECT_INPUT<<endl;
		}
		setscholarship();
		cout<<"Стипендия составила: "<<getscholarship()<<CURRENCY<<endl;
	}
	void print() {
		cout<<"ФИО: ";
		if (surname==nullptr) cout<<"не указана"<<' ';
		else cout<<surname<<' ';
		if (name==nullptr) cout<<"не указана"<<' ';
		else cout<<name<<' ';
		if (patronymic==nullptr) cout<<"не указано"<<"; ";
		else cout<<patronymic<<"; ";
		cout<<"Курс: "<<int(course)<<"; ";
		cout<<"Группа: "<<int(group)<<"; ";
		cout<<"\nОтметки за сессию: ";
		if (marks==nullptr || !strlen(marks)) cout<<"не указаны; ";
		else {
			char* p=marks;
			cout<<int(*p)-1;//по крайней мере одна отметка будет после проверки верхнего условия
			p++;
			while(*p) {
				cout<<" "<<int(*p)-1;
				p++;
			}
			cout<<"; ";
		}
		cout<<"Стипендия: "<<scholarship<<CURRENCY<<endl;
	}
	int randomInit() {
		const size_t SIZE = 20;
		const char* SURNAMES[SIZE] = {"Барадулин","Малкович","Пушкин","Иванов","Ковалев","Петров","Смирнов","Сидоров","Шив","Камбербэтч","Петухова","Терешкова","Ковалева","Тупалева","Звонарева","Козлова","Карпович","Малевич","Амидала","Органа"};
		const char* NAMES[SIZE] = {"Владимир","Джон","Сергей","Игорь","Владислав","Боб","Павел","Максимилиан","Палпатин","Бенедикт","Мария","Екатерина","Маргарита","Анна","Мальвина","Дарья","Юлия","Нюша","Падме","Лея"};
		const char* PATRONYMICS[SIZE] = {"Путятович","Пантелеевич","Гаврилович","Тишилович","Владимирович","Мовеславович","Бориславович","Вячкович","Витовтович","Миндовгович","Добролюбовна","Гориславовна","Остаповна","Рюриковна","Ягайловна","Карловна","Фельмонтовна","Пересветовна","Святогоровна","Гавриловна"};
		size_t num=0;
		size_t gender=0;//мужской
		size_t minMark=0;
		if (rand()%2) gender=SIZE/2;//женский
		setsurname(SURNAMES[rand()%(SIZE/2)+gender]);
		setname(NAMES[rand()%(SIZE/2)+gender]);
		setpatronymic(PATRONYMICS[rand()%(SIZE/2)+gender]);
		course=rand()%(MAX_COURSE-MIN_COURSE+1)+MIN_COURSE;
		group=rand()%NUM_OF_GROUPS+1;
		num=rand()%(MAX_NUM_OF_MARKS-MIN_NUM_OF_MARKS+1)+MIN_NUM_OF_MARKS;
		if (marks!=nullptr) delete[] marks;
		try{
			marks = new char[num+1];
		}
		catch(...) {
			cout<<ERROR_MESSAGE<<endl;
			exit(0);
		}
		minMark=(rand()%(MAX_MARK-MIN_MARK+2-VARIATION)+MIN_MARK);//чтобы отметки не крайне сильно отличались в пределах одного студента , вводится минимальная отметка данного студента, от которой будет отталкиваться рандом (чтобы избежать отметок как "5 10 1 6", из-за чего почти не бывает "отличников") с разбросом VARIATION
		for (size_t i=0; i<num; i++) {
			marks[i]=((rand()%(VARIATION)+minMark)+1);
		}
		marks[num]=0;
		return 0;
	};
	int save(ofstream& file) {
		file.write(surname, strlen(surname)+1);
		file.write(name, strlen(name)+1);
		file.write(patronymic, strlen(patronymic)+1);
		file.write(marks, strlen(marks)+1);
		file.write(&course, 1);
		file.write(&group, 1);
		file.write((char *)&scholarship, sizeof(scholarship));
		return 0;
	};
	int load(ifstream& file) {
		char tmp[MAX_LENGTH_WORD+1]={};
		char tmp1=0;
		float tmpFloat=0;
		if (file) file.getline(tmp, MAX_LENGTH_WORD+1,'\0');
		else return 1;
		if (setsurname(tmp)) return 1;//чтобы если файл не валидный - не считывать дальше
		if (file) file.getline(tmp, MAX_LENGTH_WORD+1,'\0');
		else return 1;
		if (setname(tmp)) return 1;//чтобы если файл не валидный - не считывать дальше
		if (file) file.getline(tmp, MAX_LENGTH_WORD+1,'\0');
		else return 1;
		if (setpatronymic(tmp)) return 1;//чтобы если файл не валидный - не считывать дальше
		if (file) file.getline(tmp, MAX_LENGTH_WORD+1,'\0');
		else return 1;
		if (setmarks(tmp)) return 1;//чтобы если файл не валидный - не считывать дальше
		if (file) file.get(tmp1);
		else return 1;
		if (setcourse(tmp1)) return 1;//чтобы если файл не валидный - не считывать дальше
		if (file) file.get(tmp1);
		else return 1;
		if (setgroup(tmp1)) return 1;//чтобы если файл не валидный - не считывать дальше
		file.read((char *)&tmpFloat,sizeof(tmpFloat));
		if (setscholarship(tmpFloat)) return 1;//чтобы если файл не валидный - не считывать дальше
		return 0;
	};
};
typedef SIZE_TYPE fff(Student*,SIZE_TYPE&);
typedef fff *pfff;
SIZE_TYPE generateStudents(Student *Students, SIZE_TYPE& N) {
	for(SIZE_TYPE i=0; i<N; i++) {
		Students[i].randomInit();
	}
	return 0;
}
SIZE_TYPE taskInfo(Student *Students, SIZE_TYPE& N) {
	cout<<"Текст условия задачи:\n"<<TaskInformation<<'\n';
	return 0;
}
SIZE_TYPE printStudents(Student *Students, SIZE_TYPE& N) {
	cout<<"СПИСОК ВСЕХ СТУДЕНТОВ:"<<endl;
	for (SIZE_TYPE i=0; i<N; i++) {
		cout<<"________________________________________________________________________"<<endl;
		Students[i].print();
	}
	return 0;
}
SIZE_TYPE printStudentsToCharacteristic(Student *Students, SIZE_TYPE& N) {
	int userNum=0;
	cout<<"Определенить студентов, сдавших сессию на: "<<endl;
	cout<<"	1) Отлично"<<endl;
	cout<<"	2) Хорошо и отлично"<<endl;
	cout<<"	3) Удовлетворительно"<<endl;
	cout<<"	4) Неудовлетворительно"<<endl;
	cin>>userNum;
	switch(userNum) {
		case 1:
			cout<<"СПИСОК СТУДЕНТОВ, СДАВШИХ СЕССИЮ НА ОТЛИЧНО:"<<endl;
			for (SIZE_TYPE i=0; i<N; i++) {
				if (Students[i].isHonoursStudy()) cout<<"________________________________________________________________________\n"<<Students[i]<<endl;
			}
			break;
		case 2:
			cout<<"СПИСОК СТУДЕНТОВ, СДАВШИХ СЕССИЮ НА ХОРОШО И ОТЛИЧНО:"<<endl;
			for (SIZE_TYPE i=0; i<N; i++) {
				if (Students[i].isGoodStudy()) cout<<"________________________________________________________________________\n"<<Students[i]<<endl;
			}
			break;
		case 3:
			cout<<"СПИСОК СТУДЕНТОВ, СДАВШИХ СЕССИЮ НА УДОВЛЕТВОРИТЕЛЬНО:"<<endl;
			for (SIZE_TYPE i=0; i<N; i++) {
				if (Students[i].isNormalStudy()) cout<<"________________________________________________________________________\n"<<Students[i]<<endl;
			}
			break;
		case 4:
			cout<<"СПИСОК СТУДЕНТОВ, СДАВШИХ СЕССИЮ НА НЕУДОВЛЕТВОРИТЕЛЬНО:"<<endl;
			for (SIZE_TYPE i=0; i<N; i++) {
				if (Students[i].isBadStudy()) cout<<"________________________________________________________________________\n"<<Students[i]<<endl;
			}
			break;
		default:
			return 1;
	}
	return 0;
}
SIZE_TYPE numsOfBadStudents(Student *Students, SIZE_TYPE& N) {
	const size_t NUM_OF_COUSRES=MAX_COURSE-MIN_COURSE+1;
	size_t badStudents[NUM_OF_COUSRES][NUM_OF_GROUPS];
	size_t badStudentsForCourses[NUM_OF_COUSRES];
	size_t i=0,j=0;
	for (i=0; i<NUM_OF_COUSRES; i++) {
		badStudentsForCourses[i]=0;
		for (j=0; j<NUM_OF_GROUPS; j++) {
			badStudents[i][j]=0;
		}
	}
	for (i=0; i<N; i++) {
		if (Students[i].isBadStudy()) {
			badStudents[int(Students[i].getcourse())-MIN_COURSE][int(Students[i].getgroup())-1]+=1;
			badStudentsForCourses[int(Students[i].getcourse())-MIN_COURSE]+=1;
		}
	}
	cout<<"КОЛИЧЕСТВА СТУДЕНТОВ, СДАВШИХ СЕССИЮ НА НЕУДОВЛЕТВОРИТЕЛЬНО:"<<endl;
	for (i=0; i<NUM_OF_COUSRES; i++) {
		cout<<"Курс "<<i+MIN_COURSE<<endl;
		for (j=0; j<NUM_OF_GROUPS; j++) {
			cout<<"	Группа "<<j+1<<": "<<badStudents[i][j]<<endl;
		}
		cout<<"	Итого: "<<badStudentsForCourses[i]<<endl;
	}
	return 0;
}
SIZE_TYPE setScholarships(Student *Students, SIZE_TYPE& N) {
	cout<<"Назначение стипендий..."<<endl;
	for(size_t i=0; i<N; i++) {
		Students[i].setscholarship();
	}
	return 0;
}
void sortByMiddleMark(Student *pLeftBoarder, Student *pRightBoarder) {
	//Сортировка Хоара
	Student *i = pLeftBoarder, *j = pRightBoarder;
	float x = (*(pLeftBoarder+((pRightBoarder-pLeftBoarder)/2))).getmiddleMark();
	do {
		while((*i).getmiddleMark()>x) i++;
		while((*j).getmiddleMark()<x) j--;
		if (i<=j) {
			if (i<j) swap(*i,*j);
			i++;
			j--;
		}
	} while (i<=j);
	if (i<pRightBoarder) sortByMiddleMark(i,pRightBoarder);
	if (j>pLeftBoarder) sortByMiddleMark(pLeftBoarder,j);
}
SIZE_TYPE sortByMark(Student *Students, SIZE_TYPE& N) {
	sortByMiddleMark(Students,Students+N-1);
	return 0;
}
void sortByCourseAndScholarship(Student *pLeftBoarder, Student *pRightBoarder) {
	//Сортировка Хоара
	Student *i = pLeftBoarder, *j = pRightBoarder;
	char course = (*(pLeftBoarder+((pRightBoarder-pLeftBoarder)/2))).getcourse();
	float scholarship = (*(pLeftBoarder+((pRightBoarder-pLeftBoarder)/2))).getscholarship();
	float getcourse = 0;
	do {
		getcourse = (*i).getcourse();//чтобы дважды в условии while не вызывать метод getcourse()
		while(getcourse<course || (getcourse==course && (*i).getscholarship()<scholarship))
		{
			i++;
			getcourse = (*i).getcourse();
		}
		getcourse = (*j).getcourse();
		while(getcourse>course || (getcourse==course && (*j).getscholarship()>scholarship))
		{
			j--;
			getcourse = (*j).getcourse();
		}
		if (i<=j) {
			if (i<j) swap(*i,*j);
			i++;
			j--;
		}
	} while (i<=j);
	if (i<pRightBoarder) sortByCourseAndScholarship(i,pRightBoarder);
	if (j>pLeftBoarder) sortByCourseAndScholarship(pLeftBoarder,j);
}
SIZE_TYPE sortStudentsByCourseAndScholarship(Student *Students, SIZE_TYPE& N) {
	sortByCourseAndScholarship(Students,Students+N-1);
	return 0;
}
void sortHonoursStudents(Student **pLeftBoarder, Student **pRightBoarder) {
	//Сортировка Хоара: сортирует массив указателей на Student
	Student **i = pLeftBoarder, **j = pRightBoarder;
	Student mid = **(pLeftBoarder+((pRightBoarder-pLeftBoarder)/2));
	char course = mid.getcourse();
	char *surname = mid.getsurname();
	char *name = mid.getname();
	char *patronymic = mid.getpatronymic();
	int cmpsurname = 0;
	int cmpname = 0;
	char getcourse = 0;
	do {
		getcourse=(**i).getcourse();
		cmpsurname=strcmp((**i).getsurname(),surname);
		cmpname=strcmp((**i).getname(),name);
		while(getcourse<course || (getcourse==course && (cmpsurname<0 || (!cmpsurname && (cmpname<0 || (!cmpname && strcmp((**i).getpatronymic(),patronymic)<0)))))) {
			i++;
			getcourse=(**i).getcourse();
			cmpsurname=strcmp((**i).getsurname(),surname);
			cmpname=strcmp((**i).getname(),name);	
		}
		getcourse=(**j).getcourse();
		cmpsurname=strcmp((**j).getsurname(),surname);
		cmpname=strcmp((**j).getname(),name);
		while(getcourse>course || (getcourse==course && (cmpsurname>0 || (!cmpsurname && (cmpname>0 || (!cmpname && strcmp((**j).getpatronymic(),patronymic)>0)))))) {
			j--;	
			getcourse=(**j).getcourse();
			cmpsurname=strcmp((**j).getsurname(),surname);
			cmpname=strcmp((**j).getname(),name);
		}
		if (i<=j) {
			if (i<j) swap(*i,*j);//swap указателей на Student
			i++;
			j--;
		}
	} while (i<=j);
	if (i<pRightBoarder) sortHonoursStudents(i,pRightBoarder);
	if (j>pLeftBoarder) sortHonoursStudents(pLeftBoarder,j);
}
SIZE_TYPE printHonoursStudents(Student *Students, SIZE_TYPE& N) {
	Student** honoursStudents;//создание массива указателей на элементы массива Students (он указывает только на "отличников") и дальнейшая работа только с ним
	SIZE_TYPE i=0;
	SIZE_TYPE j=0;
	SIZE_TYPE length=0;
	char curCourse=0;
	try{
		honoursStudents = new Student*[N];//не рационально требовать для этих целей сразу память такого размера, но пока так
	}
	catch(...) {
		cout<<"Ошибка выделения памяти.";
		return 1;
	}
	for(i=0; i<N; i++) {
		if (Students[i].isHonoursStudy()) {
			honoursStudents[length]=&(Students[i]);
			length++;
		}
	}
	if (length) {
		cout<<"ОТЛИЧНИКИ ФАКУЛЬТЕТА ("<<length<<"):\n";
		sortHonoursStudents(honoursStudents,honoursStudents+length-1);
		curCourse=MIN_COURSE;
		i=0;
		for (curCourse=MIN_COURSE; curCourse<=MAX_COURSE; curCourse++) {
			cout<<"\n		КУРС "<<int(curCourse)<<endl;
			j=i;
			while(i<length && curCourse==(*(honoursStudents[i])).getcourse()) {
				//cout<<*(honoursStudents[i]);
				cout<<(*(honoursStudents[i])).getsurname()<<" "<<(*(honoursStudents[i])).getname()<<" "<<(*(honoursStudents[i])).getpatronymic()<<", ср.балл: "<<(*(honoursStudents[i])).getmiddleMark()<<endl;
				i++;
			}
			if (i==j) cout<<"Отсутствуют."<<endl;
			cout<<"________________________________________\n";
			cout<<"Доля от общего числа отличников: ";
			cout<<float(i-j)/float(length)*100<<"%"<<endl;
		}
	} else {
		cout<<"Отсутствуют отличники на факультете.\n";
	}
	delete []honoursStudents;
	return 0;
}
SIZE_TYPE inputStudent(Student *Students, SIZE_TYPE& N) {
	int studentId=0;
	cout<<"Введите индекс интересующего cтудента в массиве: ";
	cin>>studentId;
	if (studentId<0 || SIZE_TYPE(studentId)>=N) return 1;
	cout<<"РЕДАКТИРОВАНИЕ СТУДЕНТА\n";
	//cin>>Students[studentId];
	Students[studentId].input();
	return 0;
}
SIZE_TYPE outputStudentsToFile(Student *Students, SIZE_TYPE& N) {
	ofstream fileOut(FILE_NAME, ios::out | ios::binary);
	if (!fileOut) {
		cout<<"Не удалось открыть файл.\n ";  
		return 1;
	}
	for (SIZE_TYPE i=0; i<N; i++) {
		Students[i].save(fileOut);
	}
	fileOut.close();
	return 0;
}
SIZE_TYPE inputStudentsFromFile(Student *Students, SIZE_TYPE& N) {
	ifstream fileIn(FILE_NAME, ios::binary);
	SIZE_TYPE i = 0;
	if (!fileIn) {
		cout<<"Не удалось открыть файл.\n ";
		return 1;
	}
	while(i<MAX_N) {
		if (Students[i].load(fileIn)) {
			break;
		}
		i++;
	}
	N=i;
	fileIn.close();
	return 0;
}
SIZE_TYPE enrollStudent(Student *Students, SIZE_TYPE& N) {
	if (N>=MAX_N) {
		cout<<"Мест нет.\n";
		return 1;
	}
	cout<<"ЗАЧИСЛЕНИЕ:\n";
	//cin>>Students[N];
	Students[N].input();
	cout<<"ЗАЧИСЛЕН СТУДЕНТ "<<Students[N].getsurname()<<' '<<Students[N].getname()<<' '<<Students[N].getpatronymic()<<endl;
	N++;
	return 0;
}
SIZE_TYPE expelStudent(Student *Students, SIZE_TYPE& N) {
	int studentId=0;
	cout<<"Кого? (индекс интересующего cтудента в массиве): ";
	cin>>studentId;
	if (studentId<0 || SIZE_TYPE(studentId)>=N) {
		cout<<"Нет такого. ";
		return 1;
	}
	cout<<"CТУДЕНТ "<<Students[studentId].getsurname()<<' '<<Students[studentId].getname()<<' '<<Students[studentId].getpatronymic()<<" ОТЧИСЛЕН. ";
	N--;
	for (SIZE_TYPE i=studentId; i<N; i++) {
		Students[i]=Students[i+1];
	}
	return 0;
}
SIZE_TYPE exit(Student *Students, SIZE_TYPE& N) {
	exit(0);
	return 0;
}
void forEach(Student *Students, SIZE_TYPE& N, pfff pf) {
	SIZE_TYPE statusError = 0;
	statusError = pf(Students,N);
	if (statusError) {
		cout << "Не выполнено.\n";
	} else {
		cout << "Выполнено.\n";
	}
}
void menu(Student *Students, SIZE_TYPE& N) {
	int userNum = 1;
	fff * Fmenu[NUM_OF_FUNCTIONS] = {taskInfo,printStudents,printStudentsToCharacteristic,numsOfBadStudents,setScholarships,sortByMark,sortStudentsByCourseAndScholarship,printHonoursStudents,inputStudent,outputStudentsToFile,inputStudentsFromFile,enrollStudent,expelStudent,exit};
	cout << "		Объекты. Классы. Информация о студентах факультета.\n";
	while (1) {
		cout << "\nМеню:\n";
		cout << "1) Показать условие задачи\n";
		cout << "2) Показать список всех студентов\n";
		cout << "3) (а) Показать список студентов по характеристике успеваемости...\n";
		cout << "4) (b) Определенить количества студентов с неудовлетворительными оценками...\n";
		cout << "5) (c) Назначить стипендии\n";
		cout << "6) (d) Сортировки массива в порядке убывания среднего балла\n";
		cout << "7) (e) Сортировки массива по курсам, внутри курса – по полученной стипендии\n";
		cout << "8) (f) Для каждого курса вывести список отличников в алфавитном порядке...\n";
		cout << "9) Редактировать студента\n";
		cout << "10) Сохранить список студентов в файл\n";
		cout << "11) Взять список студентов из файла\n";
		cout << "12) Зачислить студента\n";
		cout << "13) Отчислить студента\n";
		cout << "14) Выход\n";
		cout << "Номер действия: ";
		cin >> userNum;
		if (userNum>=1 && userNum<=NUM_OF_FUNCTIONS) {
			forEach(Students,N,Fmenu[userNum-1]);
		} else {
			cout << "Некорректный ввод.\n";
		}
	}
}
int main() {
	setlocale(LC_ALL, "ru");
	SIZE_TYPE N = 200;
	if (N>MAX_N) return 1;
	srand(SIZE_TYPE(time(NULL)));
	Student Students[MAX_N];
	generateStudents(Students,N);
	menu(Students,N);
	system("pause");
	return 0;
}
