//ЗАДАНИЕ на 11.04.2018, задача 2.
//№2. Определить объект, содержащую информацию о студенте факультета с полями  ФИО, курс, группа, оценки в сессию (сами решите в текущую, или вообще все), размер стипендии. Создать массив объектов. Разработать функции:
//a) определения студентов, сдавших сессию на  ”отлично”, на  ”хорошо” и ”отлично”, получивших удовлетворительные оценки, получивших неудовлетворительные оценки;
//b) определения количества студентов, получивших неудовлетворительные оценки, для каждой группы и каждого курса;
//c) для каждого студента назначить размер стипендии, выбрав самостоятельно какой-нибудь критерий;
//d) сортировки массива  в порядке убывания среднего балла;
//e) сортировки массива по курсам, внутри курса – по полученной стипендии.
//f) Для каждого курса вывести список отличников в алфавитном порядке и долю (процент) их от общего числа отличников.
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <clocale>
#include <iomanip>
#include <ctime>
#include <cstring>
const char* TaskInformation = "№2. Определить объект, содержащую информацию о студенте факультета с полями  ФИО, курс, группа, оценки в сессию (сами решите в текущую, или вообще все), размер стипендии. Создать массив объектов. Разработать функции:\n a) определения студентов, сдавших сессию на  ”отлично”, на  ”хорошо” и ”отлично”, получивших удовлетворительные оценки, получивших неудовлетворительные оценки;\n b) определения количества студентов, получивших неудовлетворительные оценки, для каждой группы и каждого курса;\n c) для каждого студента назначить размер стипендии, выбрав самостоятельно какой-нибудь критерий;	\n d) сортировки массива  в порядке убывания среднего балла;\n e) сортировки массива по курсам, внутри курса – по полученной стипендии.\n f) Для каждого курса вывести список отличников в алфавитном порядке и долю (процент) их от общего числа отличников.\n";
typedef float MAIN_TYPE;
typedef unsigned int SIZE_TYPE;
const SIZE_TYPE NUM_OF_FUNCTIONS = 10;
const char* NO_CORRECT_INPUT = "Некорректный ввод, попробуйте еще раз.";
const char* CURRENCY = "$";
const size_t MAX_LENGTH_WORD = 30;
const size_t MAX_NUM_OF_MARKS = 7;
const size_t MAX_MARK = 10;
const size_t MIN_MARK = 1;
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
		try {
			if (mysurname!=nullptr) {
				surname = new char[strlen(mysurname)+1];
				strcpy(surname,mysurname);
			}
			if (myname!=nullptr) {
				name = new char[strlen(myname)+1];
				strcpy(name,myname);
			}
			if (mypatronymic!=nullptr) {
				patronymic = new char[strlen(mypatronymic)+1];
				strcpy(patronymic,mypatronymic);
			}
			if (mymarks!=nullptr) {
				marks = new char[strlen(mymarks)+1];
				strcpy(marks,mymarks);
			}
		}
		catch(...) {
			cout<<"Error.\n";
			exit(0);
		}
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
		try {
			if (other.surname!=nullptr) {
				surname = new char[strlen(other.surname)+1];
				strcpy(surname,other.surname);
			}
			if (other.name!=nullptr) {
				name = new char[strlen(other.name)+1];
				strcpy(name,other.name);
			}
			if (other.patronymic!=nullptr) {
				patronymic = new char[strlen(other.patronymic)+1];
				strcpy(patronymic,other.patronymic);
			}
			if (other.marks!=nullptr) {
				marks = new char[strlen(other.marks)+1];
				strcpy(marks,other.marks);
			}
		}
		catch(...) {
			cout<<"Error.\n";
			exit(0);
		}
	};
	~Student() {
		if (name!=nullptr) delete[] name;
		if (surname!=nullptr) delete[] surname;
		if (patronymic!=nullptr) delete[] patronymic;
		if (marks!=nullptr) delete[] marks;
	};
	void operator=(const Student &other) {
		if (this==&other) return;
		try {
			if (other.surname!=nullptr) {
				if (surname!=nullptr) delete[] surname;
				surname = new char[strlen(other.surname)+1];
				strcpy(surname,other.surname);
			}
			if (other.name!=nullptr) {
				if (name!=nullptr) delete[] name;
				name = new char[strlen(other.name)+1];
				strcpy(name,other.name);
			}
			if (other.patronymic!=nullptr) {
				if (patronymic!=nullptr) delete[] patronymic;
				patronymic = new char[strlen(other.patronymic)+1];
				strcpy(patronymic,other.patronymic);
			}
			if (other.marks!=nullptr) {
				if (marks!=nullptr) delete[] marks;
				marks = new char[strlen(other.marks)+1];
				strcpy(marks,other.marks);
			}
		}
		catch(...) {
			cout<<"Error.\n";
			exit(0);
		}
		course=other.course;
		group=other.group;
		scholarship=other.scholarship;
	};
	friend ostream& operator<<(ostream &myStream, Student &tmp) {
		cout<<"ФИО: ";
		if (tmp.surname==nullptr) cout<<"не указана"<<' ';
		else cout<<tmp.surname<<' ';
		if (tmp.name==nullptr) cout<<"не указана"<<' ';
		else cout<<tmp.name<<' ';
		if (tmp.patronymic==nullptr) cout<<"не указано"<<"; ";
		else cout<<tmp.patronymic<<"; ";
		cout<<"Курс: "<<int(tmp.course)<<"; ";
		cout<<"Группа: "<<int(tmp.group)<<"; ";
		cout<<"Отметки за сессию: ";
		if (tmp.marks==nullptr || !strlen(tmp.marks)) cout<<"не указаны"<<"; ";
		else {
			char* p=tmp.marks;
			while(*p) {
				cout<<int(*p)-1<<" ";
				p++;
			}
			cout<<"; ";
		}
		cout<<"Стипендия: "<<tmp.scholarship<<CURRENCY<<endl;
		return myStream;
	};
	friend istream& operator>>(istream &myStream, Student &tmp) {
		char tmpWord[MAX_LENGTH_WORD+1];
		short int *arrOfMarks;
		int mytmp=0;
		int N=0;
		cout<<"РЕДАКТИРОВАНИЕ СТУДЕНТА\n";
		while(1) {
			cout<<"Введите фамилию: ";
			fflush(stdin);
			cin.getline(tmpWord, MAX_LENGTH_WORD);
			if (tmp.setsurname(tmpWord)) cout<<NO_CORRECT_INPUT<<endl;
			else break;
		}
		while(1) {
			cout<<"Введите имя: ";
			fflush(stdin);
			cin.getline(tmpWord, MAX_LENGTH_WORD);
			if (tmp.setname(tmpWord)) cout<<NO_CORRECT_INPUT<<endl;
			else break;
		}
		while(1) {
			cout<<"Введите отчество: ";
			fflush(stdin);
			cin.getline(tmpWord, MAX_LENGTH_WORD);
			if (tmp.setpatronymic(tmpWord)) cout<<NO_CORRECT_INPUT<<endl;
			else break;
		}
		while(1) {
			cout<<"Введите курс: ";
			cin>>mytmp;
			if (tmp.setcourse(mytmp)) cout<<NO_CORRECT_INPUT<<endl;
			else break;
		}
		while(1) {
			cout<<"Введите номер группы: ";
			cin>>mytmp;
			if (tmp.setgroup(mytmp)) cout<<NO_CORRECT_INPUT<<endl;
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
					cout<<"Error.\n";
					exit(0);
				}
				cout<<"Введите отметки за экзамены в сессию: ";
				for (int i=0; i<N; i++) {
					cin>>mytmp;
					arrOfMarks[i]=mytmp;
				}
				if (tmp.setmarks(arrOfMarks,N)) {
					cout<<NO_CORRECT_INPUT<<endl;
					delete []arrOfMarks;
				} else {
					delete []arrOfMarks;
					break;
				}
			} else cout<<NO_CORRECT_INPUT<<endl;
		}
		tmp.setscholarship();
		cout<<"Стипендия составила: "<<tmp.getscholarship()<<CURRENCY<<endl;
		return myStream;
	};
	int setsurname(const char* mysurname) {
		if (strlen(mysurname)>MAX_LENGTH_WORD || surname==mysurname) return 1;
		if (surname!=nullptr) delete[] surname;
		surname = new char[strlen(mysurname)+1];
		strcpy(surname,mysurname);
		return 0;
	};
	int setname(const char* myname) {
		if (strlen(myname)>MAX_LENGTH_WORD || surname==myname) return 1;
		if (name!=nullptr) delete[] name;
		name = new char[strlen(myname)+1];
		strcpy(name,myname);
		return 0;
	};
	int setpatronymic(const char* mypatronymic) {
		if (strlen(mypatronymic)>MAX_LENGTH_WORD || patronymic==mypatronymic) return 1;
		if (patronymic!=nullptr) delete[] patronymic;
		patronymic = new char[strlen(mypatronymic)+1];
		strcpy(patronymic,mypatronymic);
		return 0;
	};
	int setcourse(int mycourse) {
		if (mycourse<1 || mycourse>MAX_COURSE) return 1;
		course=char(mycourse);
		return 0;
	};
	int setgroup(int mygroup) {
		if (mygroup<1 || mygroup>NUM_OF_GROUPS) return 1;
		course=char(mygroup);
		return 0;
	};
	int setmarks(short int* mymarks,int N) {
		if (N<0 || N>MAX_NUM_OF_MARKS) return 1;
		size_t i=0;
		for (i=0; i<size_t(N); i++) {//сначала проверка корректности всех отметок, а потом копирование, чтобы не портить данные объекта при неправильном вводе
			if (mymarks[i]<MIN_MARK || mymarks[i]>MAX_MARK) return 1;
		}
		if (marks!=nullptr) delete[] marks;
		marks = new char[N+1];
		for (i=0; i<size_t(N); i++) {
			marks[i]=char(mymarks[i]+1);
		}
		marks[N-1]=0;
		return 0;
	};
	float getmiddleMark() {
		if (marks==nullptr || !strlen(marks)) return 0;
		float sumMarks=0;
		char* p=marks;
		while(*p) {
			sumMarks+=(int(*p)-1);
			p++;
		}
		return sumMarks/(p-marks-1);
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
		scholarship=char(myscholarship);
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
	void printInfo() {
		cout<<"ИНФОРМАЦИЯ О СТУДЕНТЕ"<<endl;
		cout<<"Фамилия: ";
		if (surname==nullptr) cout<<"не указана"<<endl;
		else cout<<surname<<endl;
		cout<<"Имя: ";
		if (name==nullptr) cout<<"не указана"<<endl;
		else cout<<name<<endl;
		cout<<"Отчество: ";
		if (patronymic==nullptr) cout<<"не указано"<<endl;
		else cout<<patronymic<<endl;
		cout<<"Курс: "<<course;
		cout<<"Группа: "<<group;
		cout<<"Отметки за сессию: ";
		if (marks==nullptr) cout<<"не указаны"<<endl;
		else {
			char* p=marks;
			while(*p) {
				cout<<int(*p)-1<<" ";
			}
			cout<<endl;
		}
		cout<<"Стипендия: "<<group;
	};
	int randomInit() {
		const size_t SIZE = 15;
		const char* SURNAMES[SIZE] = {"Baradulin","Trumb","Pushkin","Ivanov","Kovalev","Goosak","Funny","Saddly","Cat","Dog","Palpatine","Tereshkova","Pretty","Malcovich","Cumberbatch"};
		const char* NAMES[SIZE] = {"Maria","Ivan","Vladimir","Kate","Bob","James","Serge","Ann","Artur","Barbara","Duku","Margaret","Pavel","John","Benedict"};
		const char* PATRONYMICS[SIZE] = {"Olegovich","Maksimova","Konstantinovna","Ivanovich","Vladimirovich","Olegovna","Konstantinovna","Arturovich","Pilatovna","Pavlovna","Nikolaevich","Sergeevich","Alexeevich","Rurikovich","Ostapovna"};
		size_t num=0;
		setsurname(SURNAMES[rand()%SIZE]);
		setname(NAMES[rand()%SIZE]);
		setpatronymic(PATRONYMICS[rand()%SIZE]);
		course=rand()%(MAX_COURSE-MIN_COURSE+1)+MIN_COURSE;
		group=rand()%NUM_OF_GROUPS+1;
		num=rand()%MAX_NUM_OF_MARKS+1;
		if (marks!=nullptr) delete[] marks;
		try{
			marks = new char[num+1];
		}
		catch(...) {
			cout<<"Error."<<endl;
			exit(0);
		}
		for (size_t i=0; i<num; i++) {
			marks[i]=((rand()%(MAX_MARK-MIN_MARK+1)+MIN_MARK)+1);
		}
		marks[num]=0;
		return 0;
	};
};
typedef SIZE_TYPE fff(Student*,SIZE_TYPE);
typedef fff *pfff;
SIZE_TYPE generateStudents(Student *Students, const size_t N) {
	for(size_t i=0; i<N; i++) {
		Students[i].randomInit();
	}
	return 0;
}
SIZE_TYPE taskInfo(Student *Students, const SIZE_TYPE N) {
	cout<<"Текст условия задачи:\n"<<TaskInformation<<'\n';
	return 0;
}
SIZE_TYPE printStudents(Student *Students, const SIZE_TYPE N) {
	cout<<"СПИСОК ВСЕХ СТУДЕНТОВ:"<<endl;
	for (SIZE_TYPE i=0; i<N; i++) {
		cout<<"________________________________________________________________________"<<endl;
		cout<<Students[i];
	}
	return 0;
}
SIZE_TYPE printStudentsToCharacteristic(Student *Students, const SIZE_TYPE N) {
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
SIZE_TYPE numsOfBadStudents(Student *Students, const SIZE_TYPE N) {
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
	cout<<"СПИСОК СТУДЕНТОВ, СДАВШИХ СЕССИЮ НА НЕУДОВЛЕТВОРИТЕЛЬНО:"<<endl;
	for (i=0; i<NUM_OF_COUSRES; i++) {
		cout<<"Курс "<<i+MIN_COURSE<<endl;
		for (j=0; j<NUM_OF_GROUPS; j++) {
			cout<<"	Группа "<<j+1<<": "<<badStudents[i][j]<<endl;
		}
		cout<<"	Итого: "<<badStudentsForCourses[i]<<endl;
	}
	return 0;
}
SIZE_TYPE setScholarships(Student *Students, const SIZE_TYPE N) {
	cout<<"Назначение стипендий..."<<endl;
	for(size_t i=0; i<N; i++) {
		Students[i].setscholarship();
	}
	return 0;
}
SIZE_TYPE sortByMark(Student *Students, const SIZE_TYPE N) {
	//todo
	return 0;
}
SIZE_TYPE sortByCourseAndScholarship(Student *Students, const SIZE_TYPE N) {
	//todo
	return 0;
}
SIZE_TYPE printHonoursStudents(Student *Students, const SIZE_TYPE N) {
	//todo
	return 0;
}
SIZE_TYPE inputStudent(Student *Students, const SIZE_TYPE N) {
	int studentId=0;
	cout<<"Введите номер интересующего cтудента в массиве: ";
	cin>>studentId;
	if (studentId<0 || SIZE_TYPE(studentId)>=N) return 1;
	cin>>Students[studentId];
	return 0;
}
SIZE_TYPE exit(Student *Students, const SIZE_TYPE N) {
	exit(0);
	return 0;
}
void forEach(Student *Students, const SIZE_TYPE N, pfff pf) {
	SIZE_TYPE statusError = 0;
	statusError = pf(Students,N);
	if (statusError) {
		std::cout << "Не выполнено.\n";
	} else {
		std::cout << "Выполнено.\n";
	}
}
void menu(Student *Students, const SIZE_TYPE N) {
	int userNum = 1;
	fff * Fmenu[NUM_OF_FUNCTIONS] = {taskInfo,printStudents,printStudentsToCharacteristic,numsOfBadStudents,setScholarships,sortByMark,sortByCourseAndScholarship,printHonoursStudents,inputStudent,exit};
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
		cout << "10) Выход\n";
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
	srand(SIZE_TYPE(time(NULL)));
	const SIZE_TYPE N = 10;
	Student Students[N];
	generateStudents(Students,N);
	menu(Students,N);
	system("pause");
	return 0;
}