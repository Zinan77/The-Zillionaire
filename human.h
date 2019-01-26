#ifndef _HUMAN
#define _HUMAN
#include"Player.h"
#include<string>

using namespace std;
class human :public player
{
public:
	human(string pass_in = "Unknown", string name_in = "Unknown");  //constructor
	bool gomove(int m, player &p1, player &opponent);               //control the movements of each palyer and record the steps
	bool buy_land(int ID, player &p1);                              //if the player wants to buy this land
	void pay_fine(int ID, player &p1, player &opponent);            //if the player moves to the land which belongs to his opponent
};


#endif