#include<iostream>
#include<string>
#include"land.h"
#include"Player.h"
using namespace std;


player::player()                                             //constructor
{
	set(asset_max, 0);
}

void player::set(int money, int g)                           //set the private value of the player
{
	asset = money;
	move = g;
	playerdeath = 0;
}

void player::init_land()                                     //initialize the 50 lands
{
	int pri;
	srand((unsigned)time(NULL));                             //get the price of each land from 10 to 500
	int tot_num = 50;
	for (int i = 0; i < tot_num; i++)
	{
		land square;
		pri = rand() % 490 + 11;
		square.set(i, pri, "Unknown");
		land_list.push_back(square);
	}
}

int player::get_num(string temp)                            //identify the integer number which is inside the file's content
{
	int i = 0, result;
	while (i < temp.size())
	{
		if (temp[i] >= 48 && temp[i] <= 57)                 //change the string value to the integer number
		{
			result = temp[i] - 48;
			while (temp[i + 1] >= 48 && temp[i + 1] <= 57)
			{      
				result = result * 10 + temp[i + 1] - 48;
				i++;
			}
		}
		i++;
	}
	return result;
}

void player::use_land(player &p1, player &opponent)         //file operation: if the user want log in his original account, recover its own data including the personal information and the land information
{
	string temp;
	int peo_asset, peo_move, com_asset, com_move, i = 0;
	ifstream file(p1.get_name()+".txt", ios::in);           //find the pointed file
	while (file.good() && !file.eof())
	{
		getline(file, temp);
		getline(file, temp);
		peo_asset = get_num(temp);
		getline(file, temp);
		peo_move = get_num(temp);
		getline(file, temp);
		com_asset = get_num(temp);
		getline(file, temp);
		com_move = get_num(temp);
		getline(file, temp);
		get_land(temp, p1);
		break;
	}
	file.close();
	p1.set(peo_asset,peo_move);
	opponent.set(com_asset, com_move);
}

void player::get_land(string temp, player &p1)             //identify the land information inside the file, seperate them into valid land number, land price and its owner
{
	int i = 0, n = 0;
	int tempNum, tempMon;
	string tempOwn;
	land tempSqu;
	while (i < temp.size())
	{
		if (temp[i] >= 48 && temp[i] <= 57)               //get the land number from the file
		{
			tempNum = temp[i] - 48;
			while (temp[i + 1] >= 48 && temp[i + 1] <= 57)
			{
				tempNum = tempNum * 10 + temp[i + 1] - 48;
				i++;
			}
		}

		i = i + 2;
		tempMon = temp[i] - 48;                           //get the land price from the file
		while (temp[i + 1] >= 48 && temp[i + 1] <= 57)
		{
			tempMon = tempMon * 10 + temp[i + 1] - 48;
			i++;
		}
		i = i + 2;

		tempOwn = temp[i];                
		while (temp[i + 1] != 32)
		{
			tempOwn = tempOwn + temp[i + 1];              //get the land owner from the file
			i++;
		}
		p1.land_list[n].set(tempNum, tempMon, tempOwn);   //use the obtained value to set the land information
		n++;
		i = i + 2;
	}
}
 
int player::find_user(player &p1)                         //find whether the input account is existed in the file
{
	string temp;
	bool i = false;
	ifstream file(p1.get_name()+".txt", ios::in);
	if (file)
	{
		getline(file, temp);
		if (temp == p1.get_password())                     //name and password are both correct
		{
			file.close();
			return 1;
		}
		else                                               //the password is not correct
		{
			file.close();
			return 2;
		}
	}
	else                                                   //can not find this account, need to build a new one
	{
		file.close();
		return 3;
	}
}

void player::isDead()                                     //check whether character is dead
{
	if (asset <= 0)
	{
		cout << name << " is Dead." << endl;
		system("pause");
		playerdeath = 1;	                              // give the label of death value 1
	}
}
  
bool player::dice(player &p1, player &opponent)           //simulate the dice to get a random step number to move
{
	bool i;
	cout << name << " is playing the dice to get the steps" << endl;
	int dice_num ;
	srand((unsigned)time(NULL));
	dice_num = rand() % 6 + 1;
	cout << "The result of the dice is " << dice_num ;
	i = gomove(dice_num, p1, opponent);
	if (i == false)
		return false;
}

void player::restart()                                      //if the user go through the START, add 100 to his asset
{
	move = move - 49;
	cout <<endl<< "\nCongratuation! " << name << " goes to to the START again!" << endl;
	asset = asset + 100;
	cout << name << " has got the extra 100 for this!";
	system("pause");
}

bool player::pay(double money)
{
		asset = asset - money;
		cout <<name<< " pays the money " << money << " successfully!";
		system("pause");
		return 1;
}


double player::get_fine(int ID, player &p1, player &opponent)
{
	double Fine1 = 0.1, Fine2 = 0.15, Fine3 = 0.2, money;
	if (ID != 49)
	{
		                                                       //check the land next to this land
		if ((p1.land_list[ID - 1].get_landOwner() == name || p1.land_list[ID - 1].get_landOwner() == "Unknown") && (p1.land_list[ID + 1].get_landOwner() == name || p1.land_list[ID + 1].get_landOwner() == "Unknown"))
			                                                   //the opponent does not have the land next to this land
		{
			money = p1.land_list[ID].get_landPri() * Fine1;
			cout << "This is the first kind of the fine: landPrice * 10%" << endl;
		}
		if ((p1.land_list[ID - 1].get_landOwner() != name && p1.land_list[ID - 1].get_landOwner() != "Unknown") && (p1.land_list[ID + 1].get_landOwner() == name || p1.land_list[ID + 1].get_landOwner() == "Unknown"))
			                                                   //the opponent has one land next to this land
		{
			money = p1.land_list[ID].get_landPri() * Fine2;
			cout << "This is the second kind of the fine: landPrice * 15%" << endl;
		}
		if ((p1.land_list[ID - 1].get_landOwner() == name || p1.land_list[ID - 1].get_landOwner() == "Unknown") && (p1.land_list[ID + 1].get_landOwner() != name && p1.land_list[ID + 1].get_landOwner() != "Unknown"))
		{
			money = p1.land_list[ID].get_landPri() * Fine2;
			cout << "This is the second kind of the fine: landPrice * 15%" << endl;
		}
		if ((p1.land_list[ID - 1].get_landOwner() != name && p1.land_list[ID - 1].get_landOwner() != "Unknown") && (p1.land_list[ID + 1].get_landOwner() != name && p1.land_list[ID + 1].get_landOwner() != "Unknown"))
			                                                     //the opponent has two lands next to this land
		{
			money = p1.land_list[ID].get_landPri() * Fine3;
			cout << "This is the third kind of the fine: landPrice * 20%" << endl;
		}
	}
	else
	{
		if ((p1.land_list[ID - 1].get_landOwner() == name || p1.land_list[ID - 1].get_landOwner() == "Unknown"))
		                            	                          //the opponent does not have the land next to this land
		{
			money = p1.land_list[ID].get_landPri() * Fine1;
			cout << "This is the first kind of the fine: landPrice * 10%" << endl;
		}
		if ((p1.land_list[ID - 1].get_landOwner() != name && p1.land_list[ID - 1].get_landOwner() != "Unknown"))
			                                                      //the opponent has one land next to this land
		{
			money = p1.land_list[ID].get_landPri() * Fine2;
			cout << "This is the second kind of the fine: landPrice * 15%" << endl;
		}
	}

	
	return money;
}

void player::invest_land(int ID, player &p1)                     //if the user wants to sell his personal land
{
	cout << endl << name << " chooses to invest this land!" << endl;
	cout << "The price of this land is " << p1.land_list[ID].get_landPri() << " yuan, so it can be sold in the half of its original price"<<endl ;
	cout << name << " sells this land successfully and gets " << p1.land_list[ID].get_landPri() / 2 << " yuan.";
	set(get_asset() + p1.land_list[ID].get_landPri() / 2, ID);
	p1.land_list[ID].set(p1.land_list[ID].get_landNum(), p1.land_list[ID].get_landPri(), "Unknown");
}

void show_board(player &p1, player &p2)                           //display the 50 lands with their owners and the player's movement
{
	system("cls");
	cout << endl << "Dear " << p1.get_name() << ", welcome to the Zillionaire Game!" << endl;
	                                                              //first row of the land
	cout << setfill('-') << setw(110) << "-" ;                  
	cout << endl;                                                 //second row(move display)
	cout << "|   ";
	p1.show_move(45, p1, p2) ;
	cout<< "   |";
	for (int i = 1; i < 21; i++)
	{
		cout << " ";
		p1.show_move(45 - i, p1, p2);
		cout<<" |";
	}
	cout << endl;                                                 //third row(number display + ownner)
	cout << "|" << "   45";
	p1.show_owner(45, p1, p2);
	cout<<"  |";
	for (int i = 44; i > 24; i--)
	{
		cout << " " << i;
		p1.show_owner(i, p1, p2);
		cout << "|";
	}
	cout << endl;                                                 //forth row
	cout << "|--------|" ;
	cout << setfill('-') << setw(94) << "-";
	cout << "|----|";

	                                                              //second of the land
	for (int i = 1; i < 4; i++)
	{
		cout << endl << "|   ";
		p1.show_move(45+i, p1, p2);
		cout<< "   |";
		cout << setfill(' ') << setw(94) << " " << "| ";
		p1.show_move(25 - i, p1, p2);
		cout << " |";
		cout << endl << "|   " << 45 + i ;
		p1.show_owner(45+i, p1, p2);
		cout << "  |";
		cout << setfill(' ') << setw(94) << " " << "| " << 25 - i;
		p1.show_owner(25-i, p1, p2);
		cout<< "|";
		cout << endl << "|" << setfill('-') << setw(8) << "-" << "|";
		cout << setfill(' ') << setw(94) << " " << "|----|";
	}
	cout << endl;                                                   //move display
	cout << "|   ";
	p1.show_move(49, p1, p2);
	cout << "   |";
	cout << setfill(' ') << setw(94) << " " << "| ";
	p1.show_move(21, p1, p2);
	cout << " |";
	cout << endl << "|   49";
	p1.show_owner(49, p1, p2);
	cout << "  |";
	cout << setfill(' ') << setw(94) << " " << "| 21";
	p1.show_owner(21, p1, p2);
	cout << "|";
	cout << endl << "|" << setfill('-') << setw(8) << "-" << "|";
	cout << setfill('-') << setw(94) << "-" << "|----|";
	                                                                //last floor of the land
	cout<<endl << "|   ";                                           //move display
	p1.show_move(0, p1, p2);
	cout << "   |";
	for (int i = 1; i < 21; i++)
	{
		cout << " ";
		p1.show_move(i, p1, p2); 
		cout << " |";
	}
	cout << endl;                                                   //third row
	cout << "| START";
	p1.show_owner(0, p1, p2);
	cout << " |";
	for (int i = 1; i < 10; i++)
	{
		cout << " " << i;
		p1.show_owner(i, p1, p2);
		cout << " " << "|";
	}
	for (int i = 10; i < 21; i++)
	{
		cout << " " << i;
		p1.show_owner(i, p1, p2);
		cout << "|";
	}
	cout << endl;                                                    //forth row
	cout << "|--------|";
	cout << setfill('-') << setw(94) << "-";
	cout << "|----|" << endl;
	cout << "*************************** Player "  << p1.name << "   Asset:  " << p1.asset
		<< "  VS  Opponent:  " << setw(4) << p2.name << "  ************************" ;
	//cout << p2.asset;
	cout << "\nIf you want to quit, just enter the 'Q'!" << endl<<endl;
}

void player::show_move(int i, player &p1, player&p2)                 //draw the movement of each palyer and display them on the land 
{
	p1.land_list[i].print_cur("  ");
	if (p1.get_move() == i && p2.get_move() != p1.get_move())
		p1.land_list[i].print_cur("\b\b " + p1.get_signal());
	
	if (p2.get_move() == i&& p2.get_move() != p1.get_move())
		p1.land_list[i].print_cur("\b\b " + p2.get_signal());
	
	if (p2.get_move() == p1.get_move() && p1.get_move() == i && p2.get_move() == i)
		p1.land_list[i].print_cur("\b\b" + p1.get_signal() + p2.get_signal());
}

void player::show_owner(int i, player &p1, player&p2)                 //show the owners of each land and display them
{
	p1.land_list[i].print_cur(" ");
	if (p1.land_list[i].get_landOwner() == p1.get_name())
		p1.land_list[i].print_cur("\b" + p1.get_signal());

	if (p1.land_list[i].get_landOwner() == p2.get_name())
		p1.land_list[i].print_cur("\b" + p2.get_signal());

}

void player::save(player &p1, player &opponent)                        //file operation: save the user's data when leaving the game
{
	ofstream file;
	file.open(p1.get_name()+".txt");
	if (file)
	{
		file<< p1.get_password() << endl 
			<< p1.get_asset() << endl << p1.get_move() << endl 
			<< opponent.get_asset() << endl<<opponent.get_move() << endl;
		for (int i = 0; i < 50; i++)
		{
			file << p1.land_list[i].get_landNum()<<" ";
			file << p1.land_list[i].get_landPri() << " ";
			file << p1.land_list[i].get_landOwner() << " ";
		}
		file << endl;
		file.close();
	}
	else
	{
		cout << "Can not find game.txt!" << endl;
	}
}

void player::again(player &p1)                                             //After the result has got (game finished), instal the land list again
{
	int pri;
	srand((unsigned)time(NULL));
	int tot_num = 50;
	for (int i = 0; i < tot_num; i++)
	{
		pri = rand() % 490 + 11;
		p1.land_list[i].set(i, pri, "Unknown");
	}
}