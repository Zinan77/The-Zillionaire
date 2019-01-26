#include<iostream>
#include<string>
#include"computer.h"
using namespace std;

computer::computer(string name_in)                                                               //constructor
{
	name = name_in;
	password = " ";
	playerdeath = 0;
	signal = "C";
}

bool computer::gomove(int m, player &p1, player &opponent)                                       //control the movements of each palyer and record the steps
{
	move = move + m;
	if (get_move() > 49)
	{
		restart();
	}
	cout <<endl<< name << " moves " << m << " steps to " << move << "th land!";
	system("pause");
	show_board(p1, opponent);
	if (p1.land_list[move].get_landOwner() == name)                                               //go to the its own land
	{
		cout << "Computer goes to its own land!";
		if (get_asset()<100)                                                                      //if the computer does not have enough money, invest its own land
			invest_land(move,p1);
		system("pause");
		return 1;
	}
	if (p1.land_list[move].get_landOwner() == "Unknown")                                          //go to the land without owner            
	{
		buy_land(move, p1);
	}
	                                                                                              //go to the land which is from the opponent 
	if (p1.land_list[move].get_landOwner() != "Unknown" && p1.land_list[move].get_landOwner() != name)
		pay_fine(move,p1, opponent);
	return 1;
}

bool computer::buy_land(int ID, player &p1)                                                       //if whether the computer but this land or not
{
	int result;
	if (get_asset()/2 > p1.land_list[ID].get_landPri())                                           //if the computer have enough money to buy and can still alive in nest turns
	{
		result = pay(p1.land_list[ID].get_landPri());
		cout << "Computer pays " << p1.land_list[ID].get_landPri() << " to buy this land"<<endl;
		if (result == 1)
		{
			p1.land_list[ID].set(ID, p1.land_list[ID].get_landPri(), name);
			cout << "Computer buys this land successfully!";
			system("pause");
		}
	}
	else
	{
		cout << "Computer thinks it is too expensive and does not buy this land.";                 //if the computer judge it does not have the ability to but this land
		system("pause");
	}
	return 1;
}

void computer::pay_fine(int ID, player &p1, player &opponent)                                      //if the player moves to the land which belongs to his opponent, he needs to pay the fine
{
	double fine;
	cout << "This land belongs " << p1.get_name() << " so the computer need to pay the fine!" << endl;
	fine = get_fine(ID, p1, opponent);
	cout << "This land price is: " << p1.land_list[ID].get_landPri() << " and the total fine is: " << fine << " yuan!" << endl;
	asset = asset - fine;
	p1.asset = p1.asset + fine;
	cout << "Computer's asset - " << fine << " yuan."<<endl;
	cout << p1.get_name() << "'s asset + " << fine << " yuan.";
	system("pause");
}