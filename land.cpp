#include<iostream>
#include"land.h"
#include<vector>
#include<string>
#include <time.h>
using namespace std;

land::land()
{
	set(0, 0, "Unknown");
}

void land::set(int num, int price, string name)
{
	land_Num = num;
	land_Pri = price;
	land_Owner = name;
}

int land::get_landNum()
{ 
	return land_Num;
};

int land::get_landPri()
{ 
	return land_Pri; 
};

string land::get_landOwner()
{ 
	return land_Owner;
};

void land::print_cur(string c)
{
	cout << c;
}