#pragma once
#include "Soldier.h"

//конструктор без параметров
Soldier::Soldier()
{
	fullName = "";
	number = 0;
	SetDefaultData();
}

//конструктор с параметрами ФИО и номера
Soldier::Soldier(string _fullName, int _number)
{
	if (_fullName != "")
		fullName = _fullName;

	else fullName = "Нет ФИО";

	if (_number > 0)
		number = _number;
	else
		number = -1; 

	SetDefaultData();
}

// Конструктор со всеми параметрами
Soldier::Soldier(string _fullName, int _number, int _rank, int _morale, int _countWin, int _countLouse, int _condition)
{
	fullName = _fullName;
	number = _number;
	rank = (Rank)_rank;
	morale = _morale;
	countWin = _countWin;
	countLouse = _countLouse;
	condition = (Condition)_condition; 
}

//метод установки начальных значений
void Soldier::SetDefaultData()
{
	rank = Rank::Private;
	morale = 10;
	countWin = 0;
	countLouse = 0;
	condition = Condition::In_the_ranks;
}

// проверка фамилии, города (места рождения), улицы, названия (журнала, мероприятия, предприятия) 
// наименования товара, производителя
bool isName(string data)
{
	if (data == "") return false;

	//перечень допустимых символов
	string str_name(" -абвгдеёжзийклмнопрстуфхцчшщьыэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЭЮЯ");
	// индекс первого символа, которого не должно быть в строке        
	basic_string <char>::size_type indexCh = -1;
	// Поиск первого символа в строке  my_str, который не является ни одним из элементов строки str_name
	// Возвращаемое значение - индекс первого символа, который не является элементом строки str_name
	indexCh = data.find_last_not_of(str_name); // поиск недопустимых символов
	if ((indexCh != -1) || (data[0] == ' ') || (data[0] == '-'))
		// Строка содержит недопустимые символы или начинается с пробела/дефиса                
		return false;
	return true;
}

// Проверка номера на корректность
bool ChechkNumber(int number)
{
	int count = 0;

	while (number != 0)
	{
		count++;
		number /= 10;
	}

	return count == 6 ? true : false;
}

//метод ввода данных
void Soldier::EnterData()
{
	string fullName;
	int number;

	cout << "Введите ФИО солдата: ";
	while (1)
	{
		cin.ignore(cin.rdbuf()->in_avail()); //очистка входного потока
		getline(cin,fullName);
		if (isName(fullName) == true)
		{
			this->fullName = fullName;
			break;
		}
		cout << "ФИО содержит недопустимые символы, начинается с пробела/дефиса или является пустой строкой, повторите попытку: ";
	}

	cout << "\nВведите номер солдата: ";
	while (1)
	{
		cin.ignore(cin.rdbuf()->in_avail()); //очистка входного потока
		cin >> number;
		if (number > 0 && ChechkNumber(number))
		{
			this->number = number;
			break;
		}
		cout << "Номер не может быть отрицательным или превышать 6 цифр, повторите попытку: ";
	}
}

//метод вывода данных
void Soldier::PrintData() const
{
	cout << endl << "Имя солдата: " << GetName() << endl;
	cout << "Номер солдата: " << GetNumber() << endl;
	cout << "Звание солдата: " << GetRank() << endl;
	cout << "Мораль: " << GetMorale() << endl;
	cout << "Количество побед: " << GetCountWin() << endl;
	cout << "Количество поражений: " << GetCountLouse() << endl;
	cout << "Состояние солдата: " << GetCondition() << endl << endl;
	cout << "________________________________________________________________\n";
}
//метод получения ФИО
string Soldier::GetName() const
{
	return fullName;
}

// метод получения звания
string Soldier::GetRank() const
{
	switch (rank)
	{
	case Rank::Private:
		return "Рядовой";
	case Rank::Corporal:
		return "Ефрейтор";
	case Rank::Ensign:
		return "Прапорщик";
	case Rank::Foreman:
		return "Старшина";
	} 
}

// метод получаения морали
int Soldier::GetMorale() const
{
	return morale; 
}

void Soldier::SetRank(Rank _rank)
{
	rank = _rank;
}

// метод повышения звания
void Soldier::UpRank()
{
	if ((int)rank < 4) //выше генерала повысить нельзя
	{
		rank = (Rank)((int)rank + 1); //повышаем звание
		morale++; // повышаем мораль
	}
}

// метод понижения звания
void Soldier::DownRank()
{
	if ((int)rank > 0) //ниже Рядового понизить нельзя
	{
		rank = (Rank)((int)rank - 1); //понижаем звание

		if(morale > 0)
			morale--; // понижаем мораль
	}
}

// метод получения количества выигранных сражений
int Soldier::GetCountWin() const
{
	return countWin; 
}

// метод получения количества проигранных сражений
int Soldier::GetCountLouse() const
{
	return countLouse;
}

// метод добавления победы
void Soldier::AddWin(Condition newCondition)
{
	//добавляем победу только тем, кто был In_the_ranks
	if (condition == Condition::In_the_ranks)
	{
		rank = (rank < 2) ? (Rank)((int)rank + 1) : rank; // повышаем звание
		countWin++; // увеличиваем счётчик побед
		if (newCondition < condition && morale > 0) // если состояние изменилось в худшую сторону, то понижаем мораль
			morale--;
		else // иначе повышаем мораль
			morale++;
		condition = newCondition; // присваваем солдату новое состояние
	}
}

// метод добавления поражений
void Soldier::AddLouse(Condition newCondition)
{
	//добавляем поражение только тем, кто был In_the_ranks
	if (condition == Condition::In_the_ranks && rank < 3)
	{
		rank = (rank > 0) ? (Rank)((int)rank - 1) : rank; // понижаем звание
		countLouse++; // увеличиваем счётчик поражений
		if (morale > 0) //  понижаем мораль
			morale--;

		condition = newCondition; // присваваем солдату новое состояние
	}
}

// метод получения состояния солдата
string Soldier::GetCondition() const
{
	switch (condition)

	{
	case Condition::In_the_ranks:
		return "В строю";
	case Condition::Wounded:
		return "Ранен";
	case Condition::Dead:
		return "Убит";
	}
}

// метод получения номера
int Soldier::GetNumber() const
{
	return number; 
}

// метод возвращения номера звания
int Soldier::GetRangInt() const
{
	return (int)rank;
}

// метод возвращение номера состояния
int Soldier::GetConditionInt() const
{
	return (int)condition;
}

// метод лечения солдата
void Soldier::Heal()
{
	// Deadого солдата вылечить нельзя
	if(condition == Condition::Wounded)
		condition = Condition::In_the_ranks; 
}