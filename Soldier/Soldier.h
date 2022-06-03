#pragma once
#include <iostream>
using namespace std;

enum Condition
{
	¬_строю,
	–анен, 
	”бит
};

enum Rank
{
	–€довой,
	≈фрейтор, 
	—таршина,
	ѕрапорщик,
};

class Soldier
{
private:
	string fullName;
	int number;
	Rank rank;
	int morale;
	int countWin;
	int countLouse;
	Condition condition; 
	void SetDefaultData(); //метод установки начальных значений
public:
	Soldier(); //конструктор по умолчанию
	Soldier(string _fullName, int _number);  // конструктор с параметрами ‘»ќ, номер
	void EnterData(); // метод ввода данных
	void PrintData() const; //метод вывода данных
	string GetName() const; // метод получени€ имени
	string GetRank() const; // метод получени€ звани€
	int GetMorale() const; // метод получени€ морали
	void UpRank(); // метод повышени€ ранга
	void DownRank(); // метод понижени€ ранга
	int GetCountWin() const; // метод получени€ количетва побед
	void AddWin(Condition newCondition); // метод добавлени€ победы
	int GetCountLouse() const; // метод получени€ количества поражений
	void AddLouse(Condition newCondition); // метод добавлени€ поражени€
	string GetCondition() const; // метод получени€ состо€ни€
	int GetNumber() const; // метод получени€ номера
	void Heal(); // метод лечени€ солдата
};