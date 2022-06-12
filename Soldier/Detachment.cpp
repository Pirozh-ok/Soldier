#pragma once
#include "Detachment.h"
#include <algorithm>

int Detachment::GetCountSoldier()
{
	return soldiers.size();
}

//метод добавления солдата
void Detachment::AddSoldier()
{
	Soldier s;
	s.EnterData();

	for (int i = 0; i < soldiers.size(); i++)
		if (s.GetName() == soldiers[i].GetName() || s.GetNumber() == soldiers[i].GetNumber())
			throw exception("Солдат с таким именем или номером уже есть в отряде!");

	soldiers.push_back(s);
	cout << "Солдат был добавлен в отряд!" << endl;
}

//метод удаления солдата по имени и номеру
void Detachment::RemoveSoldier()
{
	string name;
	int number;

	cout << "Введите ФИО солдата, которого хотите исключить: ";
	cin.ignore(cin.rdbuf()->in_avail()); //очитска входного потока
	getline(cin,name);
	cout << "Введите номер солдата, которого хотите исключить: ";
	cin.ignore(cin.rdbuf()->in_avail()); //очитска входного потока
	cin >> number;
	
	for (int i = 0; i < soldiers.size(); i++)
	{
		if (soldiers[i].GetName() == name && soldiers[i].GetNumber() == number)
		{
			soldiers.erase(i);
			cout << "Солдат был исключён!" << endl;
			return;
		}
	}
	cout << "Солдата с таким именем в отряде не обнаружено!" << endl;
}

//метод удаления всех убитых солдат
void Detachment::RemoveDeadSoldier()
{
	if (soldiers.size() > 0)
	{
		//проходимся по всем солдатам и удаляем тех, у кого статус - Убит
		for (int i = 0; i < soldiers.size(); i++)
		{
			if (soldiers[i].GetCondition() == "Убит")
			{
				soldiers.erase(i);
				i--;
			}
		}
		cout << "Все Убитые солдаты исключены из отряда!" << endl;
	}
	else cout << "В отряде ещё нет солдат!" << endl;
}

//метод учёта результатов сражения
void Detachment::AccountResult(ResultBattle result)
{
	//если победа, то добавляем каждому солдату победу, и распределяем новые состояния солдатов согласно результатам битвы
	if (result.isWin)
	{
		countWin++;

		for (int i = 0, j = 0, k = 0; i < soldiers.size(); i++)
		{
			if (j < result.countWounded && soldiers[i].GetCondition() == "В строю")
			{
				soldiers[i].AddWin(Condition::Wounded);
				j++;
			}
			else if (k < result.countDead && soldiers[i].GetCondition() == "В строю")
			{
				soldiers[i].AddWin(Condition::Dead);
				k++;
			}
			else soldiers[i].AddWin(Condition::In_the_ranks);
		}
	}
	//иначе присваиваем поражения и также новые состояния солдат
	else
	{
		countLouse++;

		for (int i = 0, j = 0, k = 0; i < soldiers.size(); i++)
			if (j < result.countWounded)
			{
				soldiers[i].AddLouse(Condition::Wounded);
				j++;
			}
			else if (k < result.countDead)
			{
				soldiers[i].AddLouse(Condition::Dead);
				k++;
			}
			else soldiers[i].AddLouse(Condition::In_the_ranks);
	}
	cout << "Результаты сражения отряда учтены!" << endl;
}

//метод получения количества побед отряда
int Detachment::GetCountWin() const
{
	return countWin;
}

//метод получения количетсва поражений отряда
int Detachment::GetCountLouse() const
{
	return countLouse;
}

//метод вывода информации об отряде
void Detachment::PrintInfo()
{
	if (soldiers.size() < 1)
	{
		cout << "В отряде ещё нет солдат!" << endl;
		return;
	}

	Sort();

	cout << "Количество побед отряда: " << countWin << endl;
	cout << "Количество поражений отряда: " << countLouse << endl;
	cout << "В отряде содержится "<< soldiers.size() << " солдат: " << endl;
	for (int i = 0; i < soldiers.size(); i++)
	{
		cout << i + 1;
		soldiers[i].PrintData();
		cout << endl;
	}
}

struct myclass {
	bool operator() (Soldier i, Soldier j) { return (i.GetName() < j.GetName()); }
} myobject;

//метод сортировки отряда по имени
void Detachment::Sort()
{
	sort(soldiers.begin(), soldiers.end(), myobject);
}

//метод получения количества живых солдат в отряде
int Detachment::GetCountLiveSoldier()
{
	int count = 0;

	for (int i = 0; i < soldiers.size(); i++)
	{
		if (soldiers[i].GetCondition() == "В строю")
			count++;
	}

	return count; 
}

//мтеод записи отряда в файл
void Detachment::WriteToFile()
{
	ofstream file("data.txt");

	if (!file.is_open())
	{
		cout << "Не удалось открыть файл data.txt" << endl;
		return;
	}

	file.clear();

	file << to_string(countWin) << endl;
	file << to_string(countLouse) << endl;
	for (int i = 0; i < soldiers.size(); i++)
	{
		file << soldiers[i].GetName() << endl;
		file << soldiers[i].GetNumber() << endl;
		file << soldiers[i].GetRangInt() << endl;
		file << soldiers[i].GetMorale() << endl;
		file << soldiers[i].GetCountWin() << endl;
		file << soldiers[i].GetCountLouse() << endl;
		file << soldiers[i].GetConditionInt() << endl;
	}

	file.close();
	cout << "Данные успешно записаны в файл data.txt" << endl;
}

//метод считывания отряда из файла
void Detachment::ReadFromFile()
{
	ifstream file("data.txt");

	if (!file.is_open())
	{
		cout << "Не удалось открыть файл data.txt" << endl;
		return;
	}

	soldiers.clear();
	string s;
	getline(file, s);
	countWin = stoi(s);
	getline(file, s);
	countLouse = stoi(s);

	while (file.good())
	{
		string name;
		getline(file, name);
		getline(file, s);
		int number = stoi(s);
		getline(file, s);
		int rank = stoi(s);
		getline(file, s);
		int morale = stoi(s);
		getline(file, s);
		int countWin = stoi(s);
		getline(file, s);
		int countLouse = stoi(s);
		getline(file, s);
		int condition = stoi(s);
		if (name != "")
		{
			Soldier newSoldier(name, number, rank, morale, countWin, countLouse, condition);
			soldiers.push_back(newSoldier);
		}
	}

	file.close();
	cout << "Данные успешно считанны!" << endl;
}

// констуктор результата боя
ResultBattle::ResultBattle(bool _isWin, int _countDead, int _countWounded)
{
	isWin = _isWin;
	countDead = _countDead;
	countWounded = _countWounded;
}

