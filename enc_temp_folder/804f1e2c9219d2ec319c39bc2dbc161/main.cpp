#include"Detachment.h"
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

void AddSoldiers(Detachment& d)
{
	cout << "Введите количество солдат, которое хотите добавить в отряд: ";
	int enter;
	cin >> enter;
	if (enter > 0)
		for (int i = 0; i < enter; i++)
		{
			try
			{
				d.AddSoldier();
			}
			catch(exception ex)
			{
				cout << ex.what() << endl;
			}
		}
	else cout << "Количество солдат не может быть отрицательным";
}

void StartBattle(Detachment& d)
{
	if (d.GetCountSoldier() > 0)
	{
		int countDead = rand() % d.GetCountSoldier();
		int countWead = rand() % (d.GetCountSoldier() - countDead);
		int r = rand() % 2;
		bool isWin = (r == 0) ? true : false;

		string result = isWin ? "Победа" : "Поражение";
		cout << "Результат сражения: " << result << ". Количество ранненых " << countWead << ", количество Deadых " << countDead << endl;
		d.AccountResult(ResultBattle(isWin, countDead, countWead));
	}
	else cout << "В отряде ещё нет солдат!" << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	Detachment detachment;
	int enter = 0;
	while (1)
	{
		cout << "\nВыберите нужную операцию: 1 - добавить солдатов в отряд, 2 - исключить солдата из отряда по имени, 3 - вывести информацию об отряде, 4 - исключить из отряда всех Deadых солдат, 5 - провести битву, 0 - выход из программы" << endl;
		cin >> enter;

		switch (enter)
		{
		case 0:
			return 0;

		case 1:
			AddSoldiers(detachment);
			break;
		case 2:
			detachment.RemoveSoldier();
			break;
		case 3:
			detachment.PrintInfo();
			break;
		case 4:
			detachment.RemoveDeadSoldier();
			break;
		case 5:
			StartBattle(detachment);
			break;
		default: cout << "Нет операции по такому номеру!" << endl;
			break;
		}
	}
	return 0; 
}
