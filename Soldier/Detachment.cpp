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

struct myclass {
	bool operator() (Soldier i, Soldier j) { return (i.GetName() < j.GetName()); }
} myobject;

void Detachment::Sort()
{
	sort(soldiers.begin(), soldiers.end(), myobject);
}

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

ResultBattle::ResultBattle(bool _isWin, int _countDead, int _countWounded)
{
	isWin = _isWin;
	countDead = _countDead;
	countWounded = _countWounded;
}

//string Detachment::getData()
//{
//	string wins = to_string(this->GetCountWin()) + " ";
//	string loses = to_string(this->GetCountLouse());
//	return wins + loses;
//}
//
//void Detachment::writeDetachmentToFile(string &filename)
//{
//	ofstream file(filename);
//	file << getData();
//	for (auto soldier : soldiers)
//	{
//		file << soldier.GetName() << ";" << soldier.GetNumber() << ";" << soldier.GetRank() << ";" << soldier.GetCondition() << ";"
//			<< soldier.GetMorale() << ";" << soldier.GetCountWin() << ";" << soldier.GetCountLouse() << endl;
//	}
//	file.close();
//}

