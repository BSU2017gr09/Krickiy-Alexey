﻿//ЗАДАНИЕ на 04.04.2018, задача 15.
//№15. В структуре хранится информация о движении самолётов: номер рейса, пункт назначения, время вылета, информация о наличии свободных мест.
//a) По запросу вывести информацию об указанном рейсе.
//b) Вывести список рейсов, следующих до указанного пункта назначения.
//c) Выдать по заявке пассажира билет, если есть свободные места на указанный рейс. Предложить другой рейс, если на указанный рейс нет билетов, или вывести сообщение о невозможности вылета в указанный пункт.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <clocale>
#include <iomanip>
#include <ctime>
#include <cstring>
const char* TaskInformation = "№15. В структуре хранится информация о движении самолётов: номер рейса, пункт назначения, время вылета, информация о наличии свободных мест.\n	a) По запросу вывести информацию об указанном рейсе.\n	b) Вывести список рейсов, следующих до указанного пункта назначения.\n	c) Выдать по заявке пассажира билет, если есть свободные места на указанный рейс. Предложить другой рейс, если на указанный рейс нет билетов, или вывести сообщение о невозможности вылета в указанный пункт.";
unsigned long int numOfFlight=0;
typedef float MAIN_TYPE;
typedef unsigned int SIZE_TYPE;
const unsigned int MAX_NUM_OF_SEATS = 250;
const SIZE_TYPE NUM_OF_FUNCTIONS = 8;
using namespace std;
class Time//вспомогательный простой класс для времени
{
private:
	short int hours;
	short int minutes;
public:
	Time():hours(0), minutes(0) {};
	Time(short int myhours, short int myminutes=0):hours(myhours), minutes(myminutes) {
		hours=myhours%24;  // А почему это не сделать в списке инициализации???
		minutes=myminutes%60;
	};
	Time(const Time &other):
		hours(other.hours),
		minutes(other.minutes) 
	{};
	~Time() {};
	friend void swap(Time& first, Time& second) {  //этот феншуй объяснишь мне лично ))))
		using std::swap;
		swap(first.hours, second.hours);
		swap(first.minutes, second.minutes);
	};
	void swap(Time& other) { //этот феншуй объяснишь мне лично ))))
		using std::swap;
		swap(hours, other.hours);
		swap(minutes, other.minutes);
	};
	/*Time& operator=(const Time &other) {
		//cout<<"Работает copy"<<endl;
		if (this==&other) return (*this);
		hours=other.hours;
		minutes=other.minutes;
		return (*this);
	};*/
	Time& operator=(const Time &other) {
		//cout<<"Работает copy"<<endl;
		Time tmp(other);
		swap(tmp);
		return (*this);
	};
	Time& operator=(Time &&other) { //для POD это излишне!!!
		//cout<<"Работает move copy"<<endl;
		if (this==&other) return (*this);
		hours=other.hours;
		minutes=other.minutes;
		return (*this);
	};
	Time operator+(const Time &other) {
			//cout<<"Работает оператор +"<<endl;
			short int tmp;
			tmp=minutes+other.minutes;
			return Time(hours+other.hours+tmp/60,minutes+other.minutes+tmp%60);
	};
	bool operator<(const Time &other) {
			if (hours-other.hours) return hours<other.hours;
			else return minutes<other.minutes;
	};
	bool operator>(const Time &other) {
			if (hours-other.hours) return hours>other.hours;
			else return minutes>other.minutes;
	};
	bool operator<=(const Time &other) {
			if (hours-other.hours) return hours<=other.hours;
			else return minutes<=other.minutes;
	};
	bool operator>=(const Time &other) {
			if (hours-other.hours) return hours>=other.hours;
			else return minutes>=other.minutes;
	};
	short int getHours() {
		return hours;
	};
	short int getMinutes() {
		return minutes;
	};
	int setHours(short int myHours=0) {
		if (myHours<0 || myHours>23) return 1;
		hours=myHours;
		return 0;
	};
	int setMinutes(short int myMinutes=0) {
		if (myMinutes<0 || myMinutes>59) return 1;
		minutes=myMinutes;
		return 0;
	};
	friend ostream& operator<<(ostream &myStream, Time &tmp) {
		if (tmp.hours<=9) cout<<'0';
		cout<<tmp.hours<<':';
		if (tmp.minutes<=9) cout<<'0';
		cout<<tmp.minutes;
		return myStream;
	};
	friend istream& operator>>(istream &myStream, Time &tmp) {
		cout<<"Введите часы и минуты через пробел: ";
		short int myHours=0, myMinutes=0;
		cin>>myHours>>myMinutes;
		if (myHours>=0 && myHours<=23) tmp.hours=myHours;
		else tmp.hours=myHours%24;
		if (myMinutes>=0 && myMinutes<=59) tmp.minutes=myMinutes;
		else tmp.minutes=myMinutes%60;
		return myStream;
	};
	void printTime() {
		if (hours<=9) cout<<'0';
		cout<<hours<<':';
		if (minutes<=9) cout<<'0';
		cout<<minutes;
	};
};
class AirFlight
{
private:
	int flightId;
	char* destination;
	Time departureTime;
	unsigned int numOfseatsAvailable;
public:
	AirFlight():
		flightId(numOfFlight++),
		destination(nullptr),
		departureTime(0),
		numOfseatsAvailable(0)
	{};
	AirFlight(int myFlightId, char* myDestination=nullptr, Time myDepartureTime=Time(), unsigned int myNumOfseatsAvailable=0):
		flightId(myFlightId),
		destination(nullptr),
		departureTime(myDepartureTime),
		numOfseatsAvailable(myNumOfseatsAvailable)
	{
		try {
			destination = new char[strlen(myDestination)+1];
			strcpy(destination,myDestination);
		}
		catch(...) {
			cout<<"Error.\n";
			exit(0);
		}
	};
	AirFlight(const AirFlight &other):
		flightId(other.flightId),
		destination(nullptr),//мне кажется, что тут утечка памяти!!!!
		departureTime(other.departureTime),
		numOfseatsAvailable(other.numOfseatsAvailable)
	{
		try { 
			destination = new char[strlen(other.destination)+1];
			strcpy(destination,other.destination);
		}
		catch(...) {
			cout<<"Error.\n";
			exit(0);
		}
	};
	~AirFlight() {
		delete[] destination;
	};
	friend void swap(AirFlight& first, AirFlight& second) {
		using std::swap;
		swap(first.flightId, second.flightId);
		swap(first.destination, second.destination);
		swap(first.departureTime, second.departureTime);
		swap(first.numOfseatsAvailable, second.numOfseatsAvailable);
	};
	void swap(AirFlight& other) {
		using std::swap;
		swap(flightId, other.flightId);
		swap(destination, other.destination);
		swap(departureTime, other.departureTime);
		swap(numOfseatsAvailable, other.numOfseatsAvailable);
	};
	AirFlight& operator=(const AirFlight &other) {
		AirFlight tmp(other);
		swap(tmp);
		return (*this);
	};
	AirFlight& operator=(AirFlight &&other) {
		if (this==&other) return *this;
		flightId=other.flightId;
		destination=other.destination;
		departureTime=other.departureTime;
		numOfseatsAvailable=other.numOfseatsAvailable;
		other.destination=nullptr;
		return (*this);
	};
	friend ostream& operator<<(ostream &myStream, AirFlight &tmp) {
		cout<<"Номер рейса: "<<tmp.flightId<<" | Пункт назначения: ";
		if (tmp.destination==nullptr) cout<<"Не указан"<<endl;
		else cout<<tmp.destination<<endl;
		cout<<" | Время вылета: "<<tmp.departureTime;
		cout<<" | Количество свободных мест: "<<tmp.numOfseatsAvailable<<endl;
		return myStream;
	};
	friend istream& operator>>(istream &myStream, AirFlight &tmp) {
		const SIZE_TYPE MAX_LENGTH_CITY = 30;
		char myDestination[MAX_LENGTH_CITY];
		int myNumOfseatsAvailable=0;
		cout<<"РЕДАКТИРОВАНИЕ РЕЙСА\n";
		cout<<"Введите пункт назначения: ";
		fflush(stdin);
		cin.getline(myDestination, MAX_LENGTH_CITY);
		tmp.setDestination(myDestination);
		cout<<"Введите время вылета: ";
		cin>>tmp.departureTime;
		cout<<"Введите количество свободных мест: ";
		cin>>myNumOfseatsAvailable;
		if (myNumOfseatsAvailable>=0) tmp.setNumOfseatsAvailable(myNumOfseatsAvailable);
		return myStream;
	};
	int setFlightId(int myFlightId) {
		if (myFlightId<0) return 1;
		flightId=myFlightId;
		return 0;
	};
	int setDestination(char* myDestination) {
		if (destination==myDestination) return 1;
		delete[] destination;
		try {
			destination = new char[strlen(myDestination)+1];
			strcpy(destination,myDestination);
		}
		catch(...) {
			cout<<"Error.\n";
			exit(0);
			//return 1;
		}
		return 0;
	};
	int setDepartureTime(Time myDepartureTime) {
		departureTime=myDepartureTime;
		return 0;
	};
	int setNumOfseatsAvailable(unsigned int myNumOfseatsAvailable) {
		if (myNumOfseatsAvailable<0 || myNumOfseatsAvailable>MAX_NUM_OF_SEATS) return 1;
		else numOfseatsAvailable=myNumOfseatsAvailable;
		return 0;
	};
	int initRandom() {
		char tmpStr[]="City00";
		//tmpStr[4]+=rand()%10;
		tmpStr[5]+=rand()%10;
		setDestination(tmpStr);
		setDepartureTime(Time(rand()%24,rand()%60));
		setNumOfseatsAvailable(rand()%(MAX_NUM_OF_SEATS+1));
		return 0;
	}
	int getFlightId() {
		return flightId;
	};
	char* getDestination() {
		return destination;
	};
	Time getDepartureTime() {
		return departureTime;
	};
	unsigned int getNumOfseatsAvailable() {
		return numOfseatsAvailable;
	};
	void printInfo() {
		cout<<"ИНФОРМАЦИЯ ОБ АВИАРЕЙСЕ №"<<flightId<<endl;
		cout<<"Пункт назначения: ";
		if (destination==nullptr) cout<<"Не указан"<<endl;
		else cout<<destination<<endl;
		cout<<"Время вылета: "<<departureTime<<endl;
		cout<<"Количество свободных мест: "<<numOfseatsAvailable<<endl;
	};
	int giveTicket(unsigned int numOfTickets) {
		if (numOfseatsAvailable<numOfTickets) {
			cout<<"Недостаточно свободных мест."<<endl;
			return 1;
		}
		cout<<"	ВАШИ БИЛЕТЫ"<<endl;
		for (size_t i=0; i<numOfTickets; i++) {
			cout<<"БИЛЕТ №"<<flightId<<"."<<numOfseatsAvailable-i<<" в один конец"<<endl;
			printInfo();
			cout<<"_________________________________________"<<endl;
		}
		numOfseatsAvailable-=numOfTickets;
		return 0;
	}
};
typedef SIZE_TYPE fff(AirFlight*,SIZE_TYPE);
typedef fff *pfff;
SIZE_TYPE taskInfo(AirFlight *Flights, const SIZE_TYPE N) {
	cout<<"Текст условия задачи:\n"<<TaskInformation<<'\n';
	return 0;
}
SIZE_TYPE printFlightsToPoint(AirFlight *Flights, const SIZE_TYPE N) {
	const SIZE_TYPE MAX_LENGTH_CITY = 30;
	char userDestination[MAX_LENGTH_CITY];
	cout<<"Введите интересующий пункт назначения: ";
	fflush(stdin);
	cin.getline(userDestination, MAX_LENGTH_CITY);
	cout<<"СПИСОК АВИАРЕЙСОВ В "<<userDestination<<":"<<endl;
	for (SIZE_TYPE i=0; i<N; i++) {
		if(!strcmp(Flights[i].getDestination(),userDestination)) {
			cout<<"________________________________________________"<<endl;
			cout<<Flights[i];
		}
	}
	return 0;
}
SIZE_TYPE printFlights(AirFlight *Flights, const SIZE_TYPE N) {
	cout<<"СПИСОК ВСЕХ АВИАРЕЙСОВ:"<<endl;
	for (SIZE_TYPE i=0; i<N; i++) {
		cout<<"________________________________________________"<<endl;
		cout<<Flights[i];
	}
	return 0;
}
SIZE_TYPE initRandFlights(AirFlight *Flights, const SIZE_TYPE N) {
	for (SIZE_TYPE i=0; i<N; i++) {
		Flights[i].initRandom();
	}
	return 0;
}
SIZE_TYPE flightInfo(AirFlight *Flights, const SIZE_TYPE N) {
	int FlightId=0;
	cout<<"Введите номер рейса, информацию о котором необходимо вывести: ";
	cin>>FlightId;
	if (FlightId<0 || FlightId>=int(N)) return 1;
	Flights[FlightId].printInfo();
	return 0;
}
SIZE_TYPE giveTickets(AirFlight *Flights, const SIZE_TYPE N) {
	int FlightId=0, numOfTickets=0;
	cout<<"Введите номер интересующего рейса: ";
	cin>>FlightId;
	if (FlightId<0 || FlightId>=int(N)) return 1;
	cout<<"Введите необходимое количество билетов: ";
	cin>>numOfTickets;
	if (numOfTickets<0 || numOfTickets>=int(MAX_NUM_OF_SEATS)) return 1;
	cout<<endl;
	if (Flights[FlightId].giveTicket(numOfTickets)) {
		cout<<"АЛЬТЕРНАТИВНЫЕ РЕЙСЫ: "<<endl;
		for (SIZE_TYPE i=0; i<N; i++) {
			if (!strcmp(Flights[i].getDestination(), Flights[FlightId].getDestination()) && numOfTickets<=int(Flights[i].getNumOfseatsAvailable())) {
				cout<<"________________________________________________"<<endl;
				cout<<Flights[i];
			}
		}
		return 1;
	}
	return 0;
}
SIZE_TYPE inputFlight(AirFlight *Flights, const SIZE_TYPE N) {
	int FlightId=0;
	cout<<"Введите номер интересующего рейса: ";
	cin>>FlightId;
	if (FlightId<0 || FlightId>=int(N)) return 1;
	cin>>Flights[FlightId];
	return 0;
}
SIZE_TYPE exit(AirFlight *Flights, const SIZE_TYPE N) {
	exit(0);
	return 0;
}
void forEach(AirFlight *Flights, const SIZE_TYPE N, pfff pf) {
	SIZE_TYPE statusError = 0;
	statusError = pf(Flights,N);
	if (statusError) {
		std::cout << "Не выполнено.\n";
	} else {
		std::cout << "Выполнено.\n";
	}
}
void menu(AirFlight *Flights, const SIZE_TYPE N) {
	int userNum = 1;
	fff * Fmenu[NUM_OF_FUNCTIONS] = {taskInfo, initRandFlights, printFlights, printFlightsToPoint, flightInfo, inputFlight, giveTickets, exit};
	cout << "		Объекты. Классы. Информация о движении самолётов.\n";
	while (1) {
		cout << "\nМеню:\n";
		cout << "1) Показать условие задачи\n";
		cout << "2) Проинициализировать рейсы случайными значениями\n";
		cout << "3) Список рейсов\n";
		cout << "4) Список рейсов к указанному пунку назначения\n";
		cout << "5) Вывести информацию о рейсе\n";
		cout << "6) Редактировать рейс\n";
		cout << "7) Заказать билеты\n";
		cout << "8) Выход\n";
		cout << "Номер действия: ";
		cin >> userNum;
		if (userNum>=1 && userNum<=NUM_OF_FUNCTIONS) {
			forEach(Flights,N,Fmenu[userNum-1]);
		} else {
			cout << "Некорректный ввод.\n";
		}
	}
}
int main() {
	setlocale(LC_ALL, "ru");
	srand(SIZE_TYPE(time(NULL)));
	const SIZE_TYPE N = 10;
	AirFlight Flights[N];
	menu(Flights,N);
	system("pause");
	return 0;
}
