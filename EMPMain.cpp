//E.M.P
//Created by Fith Gateway Games

#include <iostream>
#include <string>
#include <cstring>
//#include <iomanip>
//#include <fstream>

using namespace std;

#include "movement.h"

#define NUM 64

string getCommand(string input);
string processCommand(string command);
void gameLoop();
void logo();
//string splitstring(char c[]);//inline

bool quit=false;
char userInput[64];
char * command1,* command2,* command3;

void splitString(char c[])
{
	char firstWord[NUM] = " ";
	char secondWord[NUM] = " ";
	char thirdWord[NUM] = " ";

	for(int count = 0; c[count] != '\0'; count++){
		c[count] = tolower(c[count]);
	}

	for(int i = 0; i < NUM;i++)
	{
		firstWord[i] = c[i];

		if(c[i + 1] == ' ')
		{
			for(int r = i + 2;r < NUM;r++)
			{
				secondWord[r - (i + 2)] = c[r];

				if(c[r + 1] == ' ')
				{
					for(int q = r + 2; q < NUM;q++)
					{
						thirdWord[q - (r + 2)] = c[q];
					}
					r = NUM;
				}
			}
			i = NUM;
		}
	}	
	command1=firstWord;
	command2=secondWord;
	command3=thirdWord;
	/*int s1,s2,s3;
	s1 = strlen(command1);
	s2 = strlen(command2);
	s3 = strlen(command3);
	strncpy_s(firstWord,command1,s1);
	strncpy_s(secondWord,command2,s2);
	strncpy_s(thirdWord,command3,s3);*/

	cout<<firstWord<<endl;
	cout<<command1<<endl;
}

int main(int argc, void *argv[]){
	mainMenu:
	string inputString;
	char * s;

	system("color 0a");
	logo();
	system("pause");
	system("cls");
	cout<<"Welcome to E.M.P.\n"
		<<endl
		<<"-Start\n"
		<<"-Controls\n"
		<<"-Credits\n"
		<<"-Exit\n";
	char * command;
	command = gets(userInput);
	if(!stricmp(command, "new")||!stricmp(command, "new game")||!stricmp(command, "n")){
		initialise();
		gameLoop();
	}
	else if(!stricmp(command, "credits")||!stricmp(command, "credit")||!stricmp(command, "c")){
		system("cls");
		cout<<"In loving memory of Edward Martins-Berki\n"
			<<"September 10, 2012- November 2, 2012\n"
			<<endl
			<<"Thanks for playing!\n"
			<<endl
			<<"Lead Producer: Marc Evans\n"
			<<"Lead Programmer: Eric Lemieux\n"
			<<"Lead 2D Artist: Dakota Ohori\n"
			<<"Lead Writer: Tristan Taylor\n"
			<<"Lead Level Designer: Edward Martins-Berki\n"
			<<endl
			<<"Copyright © Fifth Gateway Studio 2012\n";
		system("pause");
		system("cls");
		goto mainMenu; //returns the player to the main menu screen.
	}
	else if(!stricmp(command, "exit")||!stricmp(command, "quit")||!stricmp(command, "e")||!stricmp(command, "q")){
		exit(1);
	}
	return 0;
}

void gameLoop(){
	string userCommand;

	while(!quit){
		userCommand = getCommand("Enter: ");
		processCommand(userCommand);
	}
}

string getCommand(string input){
	//string command;
	char * command;
	bool waiting = true;

	while(waiting){
		cout<<input;
		//getline(cin, command);
		command = gets(userInput);
		//cin.getline(command,64);
		splitString(command);

		if(!stricmp(command1, "exit")||!stricmp(command1, "quit")){
			quit=true;
			return "";
		}
		if(!stricmp(command1, "north")||!stricmp(command1, "n"))
			north();
		else if(!stricmp(command1, "south")||!stricmp(command1, "s"))
			south();
		else if(!stricmp(command1, "east")||!stricmp(command1, "e"))
			east();
		else if(!stricmp(command1, "west")||!stricmp(command1, "w"))
			west();
		else if(!stricmp(command1, "move")||!stricmp(command1, "walk")||!stricmp(command1, "go")){
			if(!stricmp(command2, "north")||!stricmp(command2, "n"))
				north();
			else if(!stricmp(command2, "south")||!stricmp(command2, "s"))
				south();
			else if(!stricmp(command2, "east")||!stricmp(command2, "e"))
				east();
			else if(!stricmp(command2, "west")||!stricmp(command2, "w"))
				west();
			else if(!stricmp(command2, "down")||!stricmp(command2, "d")){}
				//TODO make the player move down
			else if(!stricmp(command2, "up")||!stricmp(command2, "u")){}
				//TODO make the player move up
			else
				cout<<"Where would you like to move?\n";
		}
		else if(!stricmp(command1, "inventory")||!stricmp(command1, "i")){}
			//TODO open inventory
		else if(!stricmp(command1, "open")||!stricmp(command1, "o")){
			if(!stricmp(command1, "door")){}
			else if(!stricmp(command1, "window")){}
			else if(!stricmp(command1, "box")){}
			else if(!stricmp(command1, "drawer")){}
			else
				cout<<"what would you like to open?";
		}
		else if(!stricmp(command1, "give")){}
			//TODO give itenms
		else if(!stricmp(command1, "punch")){}
			//TODO punch someone
			
		else
			cout<<"Sorry i didn't understand what you entered.\n";
	}
	//system("pause");
	return command;
}

string processCommand(string userCommand){
	return ("");
}

void logo(){
	cout<<"  ____| _)   _|  |    |                               \n"
		<<"  |      |  |    __|  __ \\                            \n"
		<<"  __|    |  __|  |    | | |                           \n"
		<<" _|     _| _|   \\__| _| |_|                           \n"
		<<"   ___|         |                                     \n"
		<<"  |       _\` |  __|   _ \\ \\ \\  \\   /  _\` |  |   |     \n"
		<<"  |   |  (   |  |     __/  \\ \\  \\ /  (   |  |   |     \n"
		<<" \\____| \\__,_| \\__| \\___|   \\_/\\_/  \\__,_| \\__, |     \n"
		<<"   ___|                                    ____/      \n"
		<<"  |       _\` |  __ \`__ \\    _ \\   __|                 \n"
		<<"  |   |  (   |  |   |   |   __/ \\__ \\                 \n"
		<<" \\____| \\__,_| _|  _|  _| \\___| ____/                 \n";
                                       
}