#ifndef _PLAYER
#define _PLAYER
#include"land.h"
#include <iomanip>
#include <fstream>
#include"land.h"
using namespace std;
class player
{
	friend class human;                                             //including the functions which are differenet from the computer class, just for human player
	friend class computer;                                          //including the functions which are differenet from the human class, includs the computer operations
	friend void show_board(player &p1, player &p2);                 //display the 50 lands with their owners and the player's movement
	vector <land> land_list;                                        //includes all the land information for each round player
protected:
	double asset, asset_max = 3000;                                 //the total money for each player
	string name;
	string password;
	int move;                                                       //record the postion of each player on the land 
	string signal;                                                  //people and computer have different signs which will show each movement on the land
	bool playerdeath;                                               // whether character is dead, doesn't need to be accessed or inherited
public:
	virtual bool gomove(int m, player &p1, player &opponent) = 0;   //control the movements of each palyer and record the steps
	virtual bool buy_land(int ID, player &p1) = 0;                  //if the player wants to buy this land
	virtual void pay_fine(int ID, player &p1, player &opponent) = 0;//if the player moves to the land which belongs to his opponent
	
	player();                                                       //constructor
	void set(int money, int g);                                     //set the private value of the player
	
	string get_name(){ return name; };                              //return the private value: the name of the player
	double get_asset(){ return asset; };                            //return the private value£º player's asset
	int get_asset_max(){ return asset_max; };                       //return the private value£º player's max asset
	int get_move(){ return move; };                                 //return the private value: player's move step
	string get_signal(){ return signal; };                          //return the private value: player's personal sign, Computer-'C', human-'Y'
	string get_password(){ return password; };                      //return the private value: the password of the player
	bool get_death(){ return playerdeath; };                        //return the private value: whether the player is dead or alive
	
	void init_land();                                               //initialize the 50 lands
	void use_land(player &p1, player &opponent);                    //file operation: if the user want log in his original account, recover its own data including the personal information and the land information
	void get_land(string temp, player &p1);                         //identify the land information inside the file, seperate them into valid land number, land price and its owner
	int get_num(string temp);                                       //identify the integer number inside the file's content
	int find_user(player &p1);                                      //find whether the input account is existed in the file
	void show_move(int i,  player &p1, player &p2);                 //draw the movement of each palyer and display them on the land 
	void show_owner(int i, player &p1, player &p2);                 //show the owners of each land and display them
    bool dice(player &p1, player &opponent);                        //simulate the dice to get a random step number to move
	void isDead();                                                  //check whether character is dead
	bool pay(double money);                                         //minus the received money from the whole asset
	double get_fine(int ID, player &p1, player &opponent);          //calculate the diffent fines for different situations
	void invest_land(int ID, player &p1) ;                          //if the user wants to sell his personal land
	void restart();                                                 //if the user go through the START, add 100 to his asset
	void save(player &p1, player &opponent);                        //file operation: save the user's data when leaving the game
	void again(player &p1);                                         //After the result has got (game finished), instal the land list again
};

#endif