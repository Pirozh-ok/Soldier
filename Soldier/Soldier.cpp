#pragma once
#include "Soldier.h"

//����������� ��� ����������
Soldier::Soldier()
{
	fullName = "";
	number = 0;
	SetDefaultData();
}

//����������� � ����������� ��� � ������
Soldier::Soldier(string _fullName, int _number)
{
	if (_fullName != "")
		fullName = _fullName;

	else fullName = "��� ���";

	if (_number > 0)
		number = _number;
	else
		number = -1; 

	SetDefaultData();
}

// ����������� �� ����� �����������
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

//����� ��������� ��������� ��������
void Soldier::SetDefaultData()
{
	rank = Rank::Private;
	morale = 10;
	countWin = 0;
	countLouse = 0;
	condition = Condition::In_the_ranks;
}

// �������� �������, ������ (����� ��������), �����, �������� (�������, �����������, �����������) 
// ������������ ������, �������������
bool isName(string data)
{
	if (data == "") return false;

	//�������� ���������� ��������
	string str_name(" -������������������������������������Ũ�������������������������");
	// ������ ������� �������, �������� �� ������ ���� � ������        
	basic_string <char>::size_type indexCh = -1;
	// ����� ������� ������� � ������  my_str, ������� �� �������� �� ����� �� ��������� ������ str_name
	// ������������ �������� - ������ ������� �������, ������� �� �������� ��������� ������ str_name
	indexCh = data.find_last_not_of(str_name); // ����� ������������ ��������
	if ((indexCh != -1) || (data[0] == ' ') || (data[0] == '-'))
		// ������ �������� ������������ ������� ��� ���������� � �������/������                
		return false;
	return true;
}

// �������� ������ �� ������������
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

//����� ����� ������
void Soldier::EnterData()
{
	string fullName;
	int number;

	cout << "������� ��� �������: ";
	while (1)
	{
		cin.ignore(cin.rdbuf()->in_avail()); //������� �������� ������
		getline(cin,fullName);
		if (isName(fullName) == true)
		{
			this->fullName = fullName;
			break;
		}
		cout << "��� �������� ������������ �������, ���������� � �������/������ ��� �������� ������ �������, ��������� �������: ";
	}

	cout << "\n������� ����� �������: ";
	while (1)
	{
		cin.ignore(cin.rdbuf()->in_avail()); //������� �������� ������
		cin >> number;
		if (number > 0 && ChechkNumber(number))
		{
			this->number = number;
			break;
		}
		cout << "����� �� ����� ���� ������������� ��� ��������� 6 ����, ��������� �������: ";
	}
}

//����� ������ ������
void Soldier::PrintData() const
{
	cout << endl << "��� �������: " << GetName() << endl;
	cout << "����� �������: " << GetNumber() << endl;
	cout << "������ �������: " << GetRank() << endl;
	cout << "������: " << GetMorale() << endl;
	cout << "���������� �����: " << GetCountWin() << endl;
	cout << "���������� ���������: " << GetCountLouse() << endl;
	cout << "��������� �������: " << GetCondition() << endl << endl;
	cout << "________________________________________________________________\n";
}
//����� ��������� ���
string Soldier::GetName() const
{
	return fullName;
}

// ����� ��������� ������
string Soldier::GetRank() const
{
	switch (rank)
	{
	case Rank::Private:
		return "�������";
	case Rank::Corporal:
		return "��������";
	case Rank::Ensign:
		return "���������";
	case Rank::Foreman:
		return "��������";
	} 
}

// ����� ���������� ������
int Soldier::GetMorale() const
{
	return morale; 
}

void Soldier::SetRank(Rank _rank)
{
	rank = _rank;
}

// ����� ��������� ������
void Soldier::UpRank()
{
	if ((int)rank < 4) //���� �������� �������� ������
	{
		rank = (Rank)((int)rank + 1); //�������� ������
		morale++; // �������� ������
	}
}

// ����� ��������� ������
void Soldier::DownRank()
{
	if ((int)rank > 0) //���� �������� �������� ������
	{
		rank = (Rank)((int)rank - 1); //�������� ������

		if(morale > 0)
			morale--; // �������� ������
	}
}

// ����� ��������� ���������� ���������� ��������
int Soldier::GetCountWin() const
{
	return countWin; 
}

// ����� ��������� ���������� ����������� ��������
int Soldier::GetCountLouse() const
{
	return countLouse;
}

// ����� ���������� ������
void Soldier::AddWin(Condition newCondition)
{
	//��������� ������ ������ ���, ��� ��� In_the_ranks
	if (condition == Condition::In_the_ranks)
	{
		rank = (rank < 2) ? (Rank)((int)rank + 1) : rank; // �������� ������
		countWin++; // ����������� ������� �����
		if (newCondition < condition && morale > 0) // ���� ��������� ���������� � ������ �������, �� �������� ������
			morale--;
		else // ����� �������� ������
			morale++;
		condition = newCondition; // ���������� ������� ����� ���������
	}
}

// ����� ���������� ���������
void Soldier::AddLouse(Condition newCondition)
{
	//��������� ��������� ������ ���, ��� ��� In_the_ranks
	if (condition == Condition::In_the_ranks && rank < 3)
	{
		rank = (rank > 0) ? (Rank)((int)rank - 1) : rank; // �������� ������
		countLouse++; // ����������� ������� ���������
		if (morale > 0) //  �������� ������
			morale--;

		condition = newCondition; // ���������� ������� ����� ���������
	}
}

// ����� ��������� ��������� �������
string Soldier::GetCondition() const
{
	switch (condition)

	{
	case Condition::In_the_ranks:
		return "� �����";
	case Condition::Wounded:
		return "�����";
	case Condition::Dead:
		return "����";
	}
}

// ����� ��������� ������
int Soldier::GetNumber() const
{
	return number; 
}

// ����� ����������� ������ ������
int Soldier::GetRangInt() const
{
	return (int)rank;
}

// ����� ����������� ������ ���������
int Soldier::GetConditionInt() const
{
	return (int)condition;
}

// ����� ������� �������
void Soldier::Heal()
{
	// Dead��� ������� �������� ������
	if(condition == Condition::Wounded)
		condition = Condition::In_the_ranks; 
}