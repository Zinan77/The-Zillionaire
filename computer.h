#ifndef _COMPUTER
#define _COMPUTER
#include"Player.h"
#include<string>
using namespace std;
class computer :public player
{
public:
	computer( string name_in = "Computer");              //constructor
	bool gomove(int m, player &p1, player &opponent);    //control the movements of each palyer and record the steps
	bool buy_land(int ID, player &p1);                   //whether the computer buy this land or not
	void pay_fine(int ID, player &p1, player &opponent); //if the player moves to the land which belongs to his opponent, he needs to pay the fine
};

#endif