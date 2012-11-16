//E.M.P
//Created by Fith Gateway Games

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

#include "movement.h"

#define NUM 64

string getCommand(string input);
string processCommand(string command);
void gameLoop();
void logo();
void openFile();
void mainMenu();
void inventory();

bool quit=false;
char userInput[64];
char * command1,* command2,* command3;
bool playerInventory[64];

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
	
	//TODO fix this! it is the more propper way 
	/*int s1,s2,s3;
	s1 = strlen(command1);
	s2 = strlen(command2);
	s3 = strlen(command3);
	strncpy_s(firstWord,command1,s1);
	strncpy_s(secondWord,command2,s2);
	strncpy_s(thirdWord,command3,s3);
	firstWord[s1+1]='\0'; 
	secondWord[s2+1]='\0';
	thirdWord[s3+1]='\0';

	cout<<firstWord<<endl;
	cout<<command1<<endl;*/
}

int main(int argc, void *argv[]){
	system("color 0a");

	for(int i=0;i<64;i++)
		playerInventory[i]=false;

	mainMenu();
	//openFile();
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

		if(!stricmp(command1, "look")||!stricmp(command1, "l"))
			drawArray();
			//checkPos();
		if(!stricmp(command1, "clear"))
			system("cls");
		else if(!stricmp(command1, "inventory")||!stricmp(command1, "i"))
			inventory();
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
			
		else{}
			//cout<<"Sorry i didn't understand what you entered.\n";
	}
	//system("pause");
	cout<<endl;
	return command;
}

string processCommand(string userCommand){
	return ("");
}

void logo(){
	string temp;
	ifstream logo("Assets/logo.emp");
	while(getline(logo, temp)){
		cout<<temp<<endl;
	}                           
}

void openFile(){
	string identifier;
	string dataLine;

	ifstream itemFile("items.emp");

	if(!itemFile){
		cout<<"error opening the items.emp file\n";
	}

	while(!itemFile.eof()){
		char ID[16],itemName[16],description[256];
		itemFile>>ID>>itemName>>description;

		//Replacing all of the underscores in the item file with spaces so that it is easier to read.
		for(int i=0;i<strlen(itemName);i++){
			if(itemName[i]=='_')
				itemName[i]=' ';
		}
		for(int i=0;i<strlen(description);i++){
			if(description[i]=='_')
				description[i]=' ';
		}

		if(!strcmp("itemid_02",ID)){
			cout<<"you have "<<itemName<<endl;
			cout<<"Description: "<<description<<endl;
		}
	}

	system("pause");
}

void mainMenu(){
	mainMenu:
	string inputString;
	char * s;
	
	logo();
	system("pause");
	system("cls");

	string temp;
	ifstream mainMenu("Assets/mainMenu.emp");
	while(getline(mainMenu, temp)){
		cout<<temp<<endl;
	}

	char * command;
	command = gets(userInput);
	if(!stricmp(command, "new")||!stricmp(command, "new game")||!stricmp(command, "n")||!stricmp(command, "start")){
		initialise();
		system("cls");
		//start of game, link to opening description.
		gameLoop();
	}
	else if(!stricmp(command, "credits")||!stricmp(command, "credit")||!stricmp(command, "c")){
		system("cls");

		string temp;
		ifstream credits("Assets/credits.emp");
		while(getline(credits, temp)){
			cout<<temp<<endl;
		}

		system("pause");
		system("cls");
		goto mainMenu; //returns the player to the main menu screen.
	}
	else if(!stricmp(command, "exit")||!stricmp(command, "quit")||!stricmp(command, "e")||!stricmp(command, "q")){
		exit(1);
	}
}

void inventory(){
	cout<<"In your inventory you have:\n";
	playerInventory[0]=true;

	char comparingID[16]="itemID_XX";
	ifstream itemFile("Assets/items.emp");
	
	while(!itemFile.eof()){
		char ID[16],itemName[16],description[256];
		itemFile>>ID>>itemName>>description;
		
		for(int i=0;i<5;i++)
			if(playerInventory[i]==true){
				comparingID[7]='0';		//comparingID[7]=i+48;
				comparingID[8]=i+48;	//comparingID[8]=i+49;
				
				//cout<<"1"<<comparingID<<endl;
				//cout<<"2"<<ID<<endl;
				if(!strcmp(comparingID,ID)){
					cout<<"An "<<itemName<<endl;
					//cout<<"Description: "<<description<<endl;
				}
			}
	}
}

void giveBox(){
	playerInventory[1]=true;
}