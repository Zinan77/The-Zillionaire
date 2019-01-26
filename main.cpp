#include<iostream>
#include <string>
#include<Windows.h>
using namespace std;
#include"human.h"
#include"computer.h"

bool quit()                                                                 //ask whether the user wants to quit or not
{
	char option;
	cout << "\n\t\t\t\t\Are you sure to quit? YES-'Y', NO-'N': ";
	cin >> option;
	while (option != 'Y' && option != 'N')
	{
		cout << "\n\t\t\t\t\Invalid input, again: ";
		cin >> option;
	}
	if (option == 'Y')
		return false;
}

void menu()                                                                  //display the menu on the screen
{
	system("cls");
	cout << "\n\t\t\t\t\t|-----------------------------------|\n";
	cout << "\t\t\t\t\t|            ***Welcome***          |\n";
	cout << "\t\t\t\t\t|===================================|\n";
	cout << "\t\t\t\t\t|============Please Choose==========|\n";
	cout << "\t\t\t\t\t|         1.Register.               |\n";
	cout << "\t\t\t\t\t|         2.Log in.                 |\n";
	cout << "\t\t\t\t\t|         3.Quit.                   |\n";
	cout << "\t\t\t\t\t|-----------------------------------|\n";
	cout << "\n\t\t\t\t\tYour choice is: ";
}

int game()                                                                   //the whole game process
{
	system("cls");
	string tempName;
	string tempPass;
	bool game = true, i;
	int option,find, flag = 0;
	player  *people, *opponent;
	while (flag == 0)
	{
		menu();
		cin >> option;                                                      //ask the user to choose the option from 1 to 7
		if (option != 1 && option != 2 && option != 3)                                       //valid test
		{
			cout << endl << "\t\t\t\t\tInvalid input, again£º";
			cin >> option;
		}

		switch (option)
		{
		case 1:
			cout << "\n\t\t\t\t\tPlease create your name: " ;
			cin >> tempName;		                                        // get player's name from keyboard input
			cout << "\t\t\t\t\tPlease create your password: ";
			cin >> tempPass;
			people = new human(tempPass, tempName);
			find = people->find_user(*people);
			people->init_land();
			if (find == 1 || find == 2)
			{
				cout << "\n\t\t\tThis account has already existed, please change the name!";
				Sleep(2000);
				break;
			}
			else
			{
				printf("\n\t\t\t\t\tCreate successfully!");
				opponent = new computer("Computer");
				Sleep(2000);
				flag = 1;
				people->save(*people, *opponent);
				break;
			}
		case 2:
			cout << "\n\t\t\t\t\tPlease input your name: ";
			cin >> tempName;		                                        // get player's name from keyboard input
			cout << "\t\t\t\t\tPlease input your password: " ;
			cin >> tempPass;
			people = new human(tempPass, tempName);
			opponent = new computer("Computer");
			find = people->find_user(*people);
			people->init_land();
			if (find == 1)
			{
				people->use_land(*people, *opponent);
				cout << "\n\t\t\t\t\tLog in successfully!";
				Sleep(2000);
				flag = 1;
				break;
			}
			if (find == 2)
			{
				cout << "\n\t\t\t\tWrong password! Sorry, maybe you need to register a new one!";
				Sleep(2000);
				break;
			}
			if (find == 3)
			{
				cout << "\n\t\t\t\tThis a new account (not on our list), we will create a new account for you!";
				Sleep(2000);
				flag = 1;
				people->save(*people, *opponent);
				break;
			}
		case 3:
			return 1;
			break;
		}
	}

	while (1)
	{
		show_board(*people, *opponent);
		i = people->dice(*people, *opponent);
		people->isDead();
		opponent->isDead();
		if (i == false)                                                         //the user enter 'Q' to leave
		{
			game = quit();
			if (game == false)
				break;
			else
				continue;
		}
		if (people->get_death() == 0 && opponent->get_death() == 0)            //no one is dead
		{
			show_board(*people, *opponent);
			opponent->dice(*people, *opponent);
			opponent->isDead();
		}
		if (people->get_death() == 0 && opponent->get_death() != 0)
		{
			cout << people->get_name() << ", you win the game! We will initalize you and your opponent value in the next turn";
			people->set(people->get_asset_max(), 0);                           //initialize the game
			opponent->set(opponent->get_asset_max(), 0);
			people->again(*people);
			system("pause");
			break;
		}
		if (people->get_death() != 0 && opponent->get_death() == 0)
		{
			cout << people->get_name() << ", you lose the game! We will initalize you and your opponent value in the next turn";
			people->set(people->get_asset_max(), 0);                           //initialize the game
			opponent->set(opponent->get_asset_max(), 0);
			people->again(*people);
			system("pause");
			break;
		}
	}
	people->save(*people, *opponent);
	delete people;
	delete opponent;

	return 1;
}

int main()
{
	char option;
	int play;
	while (1)
	{
		game();
		system("cls");
		cout << "\n\t\t\t\tDo you want to play again? YES-'Y' NO-'N':";
		cin >> option;
		while (option != 'Y' && option != 'N')
		{
			cout << "\n\t\t\t\t\tInvalid input, again: ";
			cin >> option;
		}
		if (option == 'N')
		{
			play = quit();
			if (play == false)
				break;
			else
				continue;
		}
	}
	cout << "\n\t\t\t\tHope to see you again!";
	return 0;
}