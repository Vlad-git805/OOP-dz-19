#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class CombatVehicle
{
protected:
	string type;
	string model;
	float health;
public:
	CombatVehicle() : type("No type"), model("No model"), health(health) {}
	CombatVehicle(string type, string model, float health) : type(type), model(model), health(health) {}
	bool IsDestroyed()
	{
		if (health <= 0)
		{
			return true;
		}
		else return false;
	}

	virtual void ShowInfo()const
	{
		cout << "Type: " << type << endl;
		cout << "Model: " << model << endl;
		cout << "Health: " << health << endl;
	}

	virtual float Attack() const = 0;
	
	virtual void Defense(float damage) = 0;
};

class Tank : public CombatVehicle
{
protected:
	int recharge_time;
	float shot_accuracy;
	float armor;
public:
	Tank() : recharge_time(0), shot_accuracy(0), armor(0) {}
	Tank(string type, string model, float health, int recharge_time, float shot_accuracy, float armor) : CombatVehicle(type, model, health), recharge_time(recharge_time), shot_accuracy(shot_accuracy), armor(armor) {}
	virtual float Attack() const final
	{
		return (100 * shot_accuracy / recharge_time);
	}

	virtual void Defense(float damage) final
	{
		health -= (damage - armor);
	}

	virtual void ShowInfo()const final
	{
		CombatVehicle::ShowInfo();
		cout << "Recharge time: " << recharge_time << endl;
		cout << "Shot accuracy: " << shot_accuracy << endl;
		cout << "Armor: " << armor << endl;
	}
};

class ArmoredCar : public CombatVehicle
{
protected:
	int number_of_weapons;
	float speed;
public:
	ArmoredCar() : number_of_weapons(0), speed(0) {}
	ArmoredCar(string type, string model, float health, int number_of_weapons, float speed) :CombatVehicle(type, model, health), number_of_weapons(number_of_weapons), speed(speed) {}
	virtual float Attack() const final
	{ 
		return (50 * number_of_weapons);
	}

	virtual void Defense(float damage) final
	{
		health -= (damage - (speed / 2));
	}

	virtual void ShowInfo()const final
	{
		CombatVehicle::ShowInfo();
		cout << "Number of weapons: " << number_of_weapons << endl;
		cout << "Speed: " << speed << endl;
	}
};

class AirDefenseVehicle : public CombatVehicle
{
protected:
	int range;
	int firing_speed;
	float mobility;
public:
	AirDefenseVehicle() : range(0), firing_speed(0), mobility(0) {}
	AirDefenseVehicle(string type, string model, float health, int range, int firing_speed, float mobility) :CombatVehicle(type, model, health), range(range), firing_speed(firing_speed), mobility(mobility) {}
	virtual float Attack() const final
	{
		return (150 + range * (firing_speed / 10));
	}

	virtual void Defense(float damage) final
	{
		health -= (damage / mobility);
	}

	virtual void ShowInfo()const final
	{
		CombatVehicle::ShowInfo();
		cout << "Range: " << range << endl;
		cout << "Firing_speed: " << firing_speed << endl;
		cout << "Mobility: " << mobility << endl;
	}
};

bool Round(CombatVehicle& cm1, CombatVehicle& cm2)
{
	int count = 1;
	while (cm1.IsDestroyed() == false && cm2.IsDestroyed() == false)
	{
		cout << "Round: " << count << "!!!" << endl;
		cout << "Info before round: " << endl;
		cout << "---- 1 ----" << endl;
		cm1.ShowInfo();
		cout << endl;
		cout << "---- 2 ----" << endl;
		cm2.ShowInfo();
		cm2.Defense(cm1.Attack());
		if (cm2.IsDestroyed())
		{
			cout << endl;
			cout << "!!!!!!!   1 win   !!!!!!!" << endl;
			cout << "---- 1 ----" << endl;
			cm1.ShowInfo();
			cout << endl;
			cout << "---- 2 ----" << endl;
			cm2.ShowInfo();
			cout << endl;
			return true;
		}
		cm1.Defense(cm2.Attack());
		if (cm1.IsDestroyed())
		{
			cout << endl;
			cout << "!!!!!!!   2 win   !!!!!!!" << endl;
			cout << "---- 1 ----" << endl;
			cm1.ShowInfo();
			cout << endl;
			cout << "---- 2 ----" << endl;
			cm2.ShowInfo();
			cout << endl;
			return false;
		}
		system("pause");
		system("cls");
		count++;
	} 
}

void War()
{
	CombatVehicle* cm1[5];
	for (int i = 0; i < 5; i++)
	{
		int rnd = rand() % 3;
		if (rnd == 0)
		{
			cm1[i] = new Tank("Tank", "228", rand() % 100 + 100, rand() % 4 + 1, 0.9, rand() % 10 + 10);
		}
		else if (rnd == 1)
		{
			cm1[i] = new ArmoredCar("Car", "lol", rand() % 50 + 100, rand() % 2 + 1, rand() % 35 + 25);
		}
		else if (rnd == 2)
		{
			cm1[i] = new AirDefenseVehicle("AirDef", "lol", rand() % 125 + 100, rand() % 1500 + 1000, rand() % 6 + 2, rand() % 15 + 5);
		}
	}

	CombatVehicle* cm2[5];
	for (int i = 0; i < 5; i++)
	{
		int rnd = rand() % 3;
		if (rnd == 0)
		{
			cm2[i] = new Tank("Tank", "228", rand() % 100 + 100, rand() % 1 + 3, 0.9, rand() % 10 + 10);
		}
		else if (rnd == 1)
		{
			cm2[i] = new ArmoredCar("Car", "lol", rand() % 50 + 100, rand() % 1 + 2, rand() % 40 + 20);
		}
		else if (rnd == 2)
		{
			cm2[i] = new AirDefenseVehicle("AirDef", "lol", rand() % 125 + 100, rand() % 1000 + 1500, rand() % 2 + 6, rand() % 5 + 15);
		}
	}

	for (int i = 0, j = 0; ;)
	{
		if (Round(*cm1[i], *cm2[j]))
		{
			j++;
		}
		else
		{
			i++;
		}
		if (j >= 5)
		{
			system("cls");
			cout << "vin comand 1" << endl;
			return;
		}
		else if (i >= 5)
		{
			system("cls");
			cout << "vin comand 2" << endl;
			return;
		}

		system("pause");
		system("cls");
	}
	
	/*int count_of_wars = 1;
	cout << "Wars: " << count_of_wars << endl;
	for (int i = 0; i < 5; i++)
	{
		Round(*cm1[i], *cm2[i]);
		system("pause");
		system("cls");
	}

	while (true)
	{
		cout << "Wars: " << count_of_wars << endl;
		bool lose1 = true;
		bool lose2 = true;
		for (int i = 0; i < 5; i++)
		{
			if (cm1[i]->IsDestroyed() == false)
			{
				lose1 = false;
			}
		}
		if (lose1 == true)
		{
			cout << "!!!!!!!  Combat Vehicle 2 WIN   !!!!!!!!" << endl;
			return;
		}
		for (int i = 0; i < 5; i++)
		{
			if (cm2[i]->IsDestroyed() == false)
			{
				lose2 = false;
			}
		}
		if (lose2 == true)
		{
			cout << "!!!!!!!  Combat Vehicle 1 WIN   !!!!!!!!" << endl;
			return;
		}
		if (lose1 == false && lose2 == false)
		{
			for (int i = 0; i < 5; i++)
			{
				if (cm1[i]->IsDestroyed() == false)
				{
					for (int j = 0; j < 5; j++)
					{
						if (cm2[j]->IsDestroyed() == false)
						{
							Round(*cm1[i], *cm2[j]);
							break;
						}
					}
				}
				break;
			}
		}
	}
	count_of_wars++;*/
}

int main()
{
	srand(time(0));

	War();

	system("pause");
	return 0;
}
 
//програма повність працює, но там при рандомі характеристик може бути таке, що при розрахунку урона або защіти, дані характеристики можуть бути або дуже великі, або маленькі, проте все працію як нада!