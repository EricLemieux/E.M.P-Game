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
void controls();
void describeItem(char item[16]);
void dropItem(char item[16]);
void printRooms();
void Talk(int talkst, int talkend);

bool quit=false;
char userInput[64];
char command1[NUM], command2[NUM], command3[NUM];
bool playerInventory[64];

void splitString(char c[]){
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
			for(int j = i + 2;j < NUM;j++)
			{
				secondWord[j - (i + 2)] = c[j];

				if(c[j + 1] == ' ')
				{
					for(int q = j + 2; q < NUM;q++)
					{
						thirdWord[q - (j + 2)] = c[q];
					}
					j = NUM;
				}
			}
			i = NUM;
		}
	}	
	for(int i=0;i<=strlen(firstWord);i++){
		command1[i]=firstWord[i];
		command1[i+1]='\0';
	}
	for(int i=0;i<=strlen(secondWord);i++){
		command2[i]=secondWord[i];
		command2[i+1]='\0';
	}
	for(int i=0;i<=strlen(thirdWord);i++){
		command3[i]=thirdWord[i];
		command3[i+1]='\0';
	}
	
	
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
	playerInventory[0]=true;

	mainMenu();
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
	char * command;
	bool waiting = true;

	while(waiting){
		cout<<input;
		command = gets_s(userInput);
		splitString(command);


		if(!_stricmp(command1, "exit")||!_stricmp(command1, "quit")){
			quit=true;
			return "";
		}
		if(!_stricmp(command1, "north")||!_stricmp(command1, "n"))
			north();
		else if(!_stricmp(command1, "south")||!_stricmp(command1, "s"))
			south();
		else if(!_stricmp(command1, "east")||!_stricmp(command1, "e"))
			east();
		else if(!_stricmp(command1, "west")||!_stricmp(command1, "w"))
			west();
		else if(!_stricmp(command1, "down")||!_stricmp(command1, "d"))
				changeLevel('-');
		else if(!_stricmp(command1, "up")||!_stricmp(command1, "u"))
				changeLevel('+');
		else if(!_stricmp(command1, "move")||!_stricmp(command1, "walk")||!_stricmp(command1, "go")){
			if(!_stricmp(command2, "north")||!_stricmp(command2, "n"))
				north();
			else if(!_stricmp(command2, "south")||!_stricmp(command2, "s"))
				south();
			else if(!_stricmp(command2, "east")||!_stricmp(command2, "e"))
				east();
			else if(!_stricmp(command2, "west")||!_stricmp(command2, "w"))
				west();
			else if(!_stricmp(command2, "down")||!_stricmp(command2, "d")){
					changeLevel('-');
			}
			else if(!_stricmp(command2, "up")||!_stricmp(command2, "u"))
					changeLevel('+');
			else
				cout<<"Where would you like to move?\n";
		}

		else if(!_stricmp(command1, "look")||!_stricmp(command1, "l"))
			checkPos();//drawArray();
		else if(!_stricmp(command1, "clear"))
			system("cls");
		else if(!_stricmp(command1, "help")||!_stricmp(command1, "controls"))
			controls();
		else if(!_stricmp(command1, "inventory")||!_stricmp(command1, "i"))
			inventory();
		//TODO fix the open command.
		else if(!_stricmp(command1, "open")||!_stricmp(command1, "o")){
			/*if(!_stricmp(command1, "door")){}
			else if(!_stricmp(command1, "window")){}
			else if(!_stricmp(command1, "box")){}
			else if(!_stricmp(command1, "drawer")){}
			else
				cout<<"what would you like to open?";*/
		}
		else if(!_stricmp(command1,"describe")||!_stricmp(command1,"view"))
			describeItem(command2);
		else if(!strcmp(command1,"drop"))
			dropItem(command2);
		else if(!strcmp(command1,"grab")||!strcmp(command1,"pick")){
			int temp = checkPos();
			cout<<"temp : "<<temp<<endl;
			if(temp!=0){
				playerInventory[temp]=true;
			}
		}
		else if(!_stricmp(command1,"talk")||!stricmp(command1,"t")){
			if(!_stricmp(command2,"Anthony")||(!_stricmp(command2,"Parker"))){
				bool talkTrue = getTalkPos(1,2,6);
				if(talkTrue){
					int convo1 = 1, convoend = 6;
					Talk(convo1, convoend);
				}
				else{
					cout<<command2<<command3<<" isn't here... \n\n";
				}
			}
		}
		else if(!strcmp(command1,"map")||!strcmp(command1,"m"))
			drawMap();
		else if(!strcmp(command1,"pr"))
			printRooms();
		else
			cout<<"Sorry i didn't understand what you entered.\n";
	}

	cout<<endl;
	for(int i=0;i<NUM;i++){
		command1[i]='\0';
		command2[i]='\0';
		command3[i]='\0';
	}
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

//Not used.
void openFile(){
	string identifier;
	string dataLine;

	ifstream itemFile("items.emp");

	if(!itemFile){
		cout<<"error opening the items.emp file\n";
	}

	while(!itemFile.eof()){
		char ID[40],itemName[32],description[256];
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
	string inputString;
	//char * s;
	
	logo();
	system("pause");
	system("cls");
	mainMenu:
	string temp;
	ifstream mainMenu("Assets/mainMenu.emp");
	while(getline(mainMenu, temp)){
		cout<<temp<<endl;
	}

	char * command;
	command = gets_s(userInput);
	if(!_stricmp(command, "new")||!_stricmp(command, "new game")||!_stricmp(command, "n")||!_stricmp(command, "start")||!_stricmp(command, "start new game")||!_stricmp(command, "ne")||!_stricmp(command, "nw")){
		initialise();
		system("cls");
		//start of game, link to opening description.
		gameLoop();
	}
	else if(!_stricmp(command, "credits")||!_stricmp(command, "credit")||!_stricmp(command, "c")){
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
	else if(!_stricmp(command, "exit")||!_stricmp(command, "quit")||!_stricmp(command, "e")||!_stricmp(command, "q")){
		exit(1);
	}
	else if(!_stricmp(command, "help")||!_stricmp(command, "controls")){
		controls();
		system("pause");
		system("cls");
		goto mainMenu;
	}
}

void inventory(){
	cout<<"In your inventory you have:\n";
	//playerInventory[0]=true;

	char comparingID[40]="itemID_XX";
	ifstream itemFile("Assets/items.emp");
	
	while(!itemFile.eof()){
		char ID[40],itemName[32],description[256];
		itemFile>>ID>>itemName>>description;
		
		for(int i=0;i<40;i++)
			if(playerInventory[i]==true){
				if(i<10){
					comparingID[7]='0';		//comparingID[7]=i+48;
					comparingID[8]=i+48;	
				}
				else if(i>=10&&i<20){
					comparingID[7]='1';
					comparingID[8]=i+38;	
				}
				else if(i>=20&&i<30){
					comparingID[7]='2';
					comparingID[8]=i+28;	
				}
				else if(i>=30&&i<40){
					comparingID[7]='3';
					comparingID[8]=i+18;	
				}
				//comparingID[8]=i+48;	//comparingID[8]=i+49;
				if(!strcmp(comparingID,ID)){
					cout<<"A "<<itemName<<endl;
					//cout<<"Description: "<<description<<endl;
				}
			}
	}
}

void describeItem(char item[16]){
	ifstream itemFile("Assets/items.emp");
	while(!itemFile.eof()){
		char ID[40],itemName[32],description[256];
		itemFile>>ID>>itemName>>description;

		for(int i=0;i<strlen(description);i++)
			if(description[i]=='_')
				description[i]=' ';
		
		if(!strcmp(item,itemName))
			cout<<"Description: "<<description<<endl;
	}
}

void dropItem(char item[16]){
	for(int i=0;i<strlen(item);i++)
		if(item[i]=='_')
			item[i]=' ';

	ifstream itemFile("Assets/items.emp");
	while(!itemFile.eof()){
		char ID[40],itemName[32],description[256];
		itemFile>>ID>>itemName>>description;
		
		int numID;
		numID=atoi(ID);

		if(!strcmp(item,itemName)){
			cout<<"droping item.\n";
			playerInventory[numID]=false;
		}
	}
}

void giveBox(){
	playerInventory[1]=true;
}

void controls(){
	string temp;
	ifstream controls("Assets/controls.emp");
	while(getline(controls, temp)){
		cout<<temp<<endl;
	}
}

void printRooms(){
	string temp;
	ifstream controls("roommmzzzz.txt");
	while(getline(controls, temp)){
		cout<<temp<<endl;
		system("pause");
	}
}

void NoSpaces(char thing[]){
	for(int i=0;i<strlen(thing);i++){
		if(thing[i]=='_')
			thing[i]=' ';
	}
}
//Imports conversation assets from text file into game, based on given position and length of conversation
void Talk(int talkst, int talkend){

	char talkid[] = {'t','a','l','k',' ',' ','\0'};

	for(int i=talkst; i<=talkend; i++){
		int div = i/10;
		if(i<=9){
			talkid[4] = '0';
			talkid[5] = i+48;
		}else{
			talkid[4] = div+48;
			talkid[5] = (i%10)+48;
		}
		cout<<talkid<<endl; //DELETE THIS, bug testing <-------------------------------------------------
		ifstream Dialog("talk.txt");
		if(!Dialog){
			cout<<"error opening the talk.txt file\n";
		}
		while(!Dialog.eof()){
			char dialog[256], character[64], talkpin[10];
			Dialog>>talkpin>>character>>dialog;
			if(!strcmp(talkid,talkpin)){
				NoSpaces(character);
				NoSpaces(dialog);
				cout<<endl<<character<<dialog<<"\n";
			}
		}
	}
}
