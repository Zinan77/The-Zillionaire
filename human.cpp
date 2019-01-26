#include<iostream>
#include<string>
#include"human.h"
using namespace std;

human::human(string pass_in, string name_in)                                    //constructor
{
	password = pass_in;
	name = name_in;
	playerdeath = 0;
	signal = "Y";
}

bool human::gomove(int m, player &p1, player &opponent)                         //control the movements of each palyer and record the steps
{
	bool i;
	char option;
	move = move + m;
	if (get_move() > 49)
		restart();
	cout << "\n" << name << " moves " << m << " steps to " << move << "th land!";
	system("pause");
	show_board(p1, opponent);
	if (land_list[move].get_landOwner() == name)                                 //go to its own land
	{
		cout << name << " goes to its own land!";
		cout << endl << name << " Would you like to invest this land, YES-'Y' NO-'N'?";
		cin >> option;
		while (option != 'Y' && option != 'N' && option != 'Q')
		{
			cout << "Invalid input, again: ";
			cin >> option;
		}
		if (option == 'Y')
		{
			invest_land(move, p1);
			system("pause");
			return 1;
		}
		if (option == 'Q')
			return false;
		if (option == 'N')
			return 1;
	}
	if (land_list[move].get_landOwner() == "Unknown")                            //go to the land without owner
	{
		i = buy_land(move, p1);
		if (i == false)
			return false;
	}
	                                                                             //go to the land which is from the opponent
	if (land_list[move].get_landOwner() != "Unknown" && land_list[move].get_landOwner() != name)
		pay_fine(move, p1,opponent);
	return 1;
}

bool human::buy_land(int ID, player &p1)                                         //if the player wants to buy this land
{
	char option;
	int result;
	cout << "Dear " << name << ", this land price is: " << land_list[ID].get_landPri() << ". Would you like to buy it, YES-'Y' NO-'N'?";
	cin >> option;
	while (option != 'Y' && option != 'N' && option != 'Q')
	{
		cout << "Invalid input, again: ";
		cin >> option;
	}
	if (option == 'Y')
	{
		if (asset < land_list[ID].get_landPri())
		{
			cout <<  "Sorry, you do not have enough money to pay it !";
			system("pause");
		}
		else
		{
			cout << "Are you sure to pay " << land_list[ID].get_landPri() << ", YES-'Y' NO-'N'?";
			cin >> option;
			while (option != 'Y' && option != 'N' && option != 'Q')
			{
				cout << "Invalid input, again: ";
				cin >> option;
			}
			if (option == 'Y')
			{
				result = pay(land_list[ID].get_landPri());
				if (result == 1)
				{
					land_list[ID].set(ID, land_list[ID].get_landPri(), name);
					cout << name << " buy this land successfully!";
					system("pause");
				}
			}
			if (option == 'Q')                                                 //input Q, quit the whole game
				return false;
		}
	}
	if (option == 'Q')                                                         //input Q, quit the whole game
		return false;
}

void human::pay_fine(int ID, player &p1, player &opponent)                     //if the player moves to the land which belongs to his opponent
{
	double fine;
	cout << "Dear " << name << ", this land belongs to your opponent so that you need to pay the fine!" << endl;
	fine = get_fine(ID, p1, opponent);
	cout << "This land price is: " << p1.land_list[ID].get_landPri() << " and the total fine is: " << fine << " yuan!" << endl;
	asset = asset - fine;
	opponent.asset = opponent.asset + fine;
	cout << name << "'s asset - " << fine << " yuan." << endl;
	cout << opponent.get_name() << "'s asset + " << fine << " yuan.";
	system("pause");
}