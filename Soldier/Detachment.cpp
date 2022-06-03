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
	cin >> name;
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
		//проходимся по всем солдатам и удаляем тех, у кого статус - убит
		for (int i = 0; i < soldiers.size(); i++)
		{
			if (soldiers[i].GetCondition() == "Убит")
			{
				soldiers.erase(i);
				i--;
			}
		}
		cout << "Все убитые солдаты исключены из отряда!" << endl;
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
			if (j < result.countWounded)
			{
				soldiers[i].AddWin(Condition::Ранен);
				j++;
			}
			else if (k < result.countDead)
			{
				soldiers[i].AddWin(Condition::Убит);
				k++;
			}
			else soldiers[i].AddWin(Condition::В_строю);
	}
	//иначе присваиваем поражения и также новые состояния солдат
	else
	{
		countLouse++;

		for (int i = 0, j = 0, k = 0; i < soldiers.size(); i++)
			if (j < result.countWounded)
			{
				soldiers[i].AddLouse(Condition::Ранен);
				j++;
			}
			else if (k < result.countDead)
			{
				soldiers[i].AddLouse(Condition::Убит);
				k++;
			}
			else soldiers[i].AddLouse(Condition::В_строю);
	}
	cout << "Результаты сражения отряда учтены!" << endl;
}

int Detachment::GetCountWin() const
{
	return countWin;
}

int Detachment::GetCountLouse() const
{
	return countLouse;
}

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

void Detachment::Sort()
{
	for (int i = 0; i < soldiers.size(); i++)
		for (int j = 0; j < soldiers.size() - 1; j++)
		{
			if (soldiers[j].GetName() < soldiers[j+1].GetName())
			{
				Soldier temp = soldiers[j]; 
				soldiers[j] = soldiers[j + 1];
				soldiers[j + 1] = temp;
			}
		}
}

ResultBattle::ResultBattle(bool _isWin, int _countDead, int _countWounded)
{
	isWin = _isWin;
	countDead = _countDead;
	countWounded = _countWounded;
}
