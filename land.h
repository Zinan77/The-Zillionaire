
#ifndef _land
#define _land
#include<vector>
using namespace std;

class land
{
protected:
	int land_Num;                                //the number of each land
	int land_Pri;                                //the price of each land
	string land_Owner;                           //the owner of each land
public:
	land();                                      //construcrtor
	void set(int num, int price, string name);   //set the information too each land
	int get_landNum();                           //return the private value: the number of the land
	int get_landPri();                           //return the private value: the price of the land
	string get_landOwner();                      //return the private value: the ownner of the land
	void print_cur(string c);                    //print the received sign on the map of the game
};

#endif