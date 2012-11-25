//E.M.P
//Created by Fith Gateway Games

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

#include "movement.h"
#include "story.h"

#define NUM 64

string getCommand(string input);
string processCommand(string command);
void gameLoop();
void logo();
void openFile();
void inventory();
void controls();
void describeItem(char item[16]);
void dropItem(char item[16]);
void printRooms();
void Talk(int talkst, int talkend);
void TalkWho(char command2[]);

bool quit=false;
char userInput[64];
char command1[NUM], command2[NUM], command3[NUM];
bool playerInventory[64];
int progress=0;

//Breaks down the player's input into smaller commands that can be proccesed.
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

//The main initialiser for the begining of the game. 
int main(int argc, void *argv[]){
	system("color 0a");

	for(int i=0;i<64;i++)
		playerInventory[i]=false;
	playerInventory[0]=true;

	logo();
	mainMenu();
	return 0;
}

//The game loop that keeps the game running until the player quits.
void gameLoop(){
	string userCommand;

	while(!quit){
		userCommand = getCommand("Enter: ");
		processCommand(userCommand);
	}
}

//Takes in the player's commands and decides what to do with them.
string getCommand(string input){
	char * command;
	bool waiting = true;
	cout<<endl;
	while(waiting){
		cout<<input;
		command = gets_s(userInput);
		splitString(command);


		if(!_stricmp(command1, "exit")||!_stricmp(command1, "quit"))
			mainMenu();
			//quitGame();
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
		else if(!_stricmp(command1, "inventory")||!_stricmp(command1, "i")||!_stricmp(command1, "inv"))
			inventory();
		//TODO fix the open command.
		else if(!_stricmp(command1, "open")||!_stricmp(command1, "o")){
			if(!_stricmp(command2, "door")||!_stricmp(command2, "d")||!_stricmp(command3, "door")){
				if(playerInventory[13] && doorCheck(1,2,7,'e')){
					cout<<"Door opened.\n";
					east();
				}
				else if(doorCheck(2,4,7,'w')){
					cout<<"Door opened.\n";
					west();
				}
			}
			else
				cout<<"what would you like to open?\n";
		}
		else if(!_stricmp(command1,"describe")||!_stricmp(command1,"view"))
			describeItem(command2);
		else if(!strcmp(command1,"drop"))
			dropItem(command2);
		else if(!strcmp(command1,"grab")||!strcmp(command1,"pick")||!strcmp(command1,"take")){
			int temp = checkItemPos();
			if(temp!=0){
				playerInventory[temp]=true;
				cout<<endl<<"You picked up a "<<nameItem(temp);
			}
		}
		else if(!_stricmp(command1,"talk")||!_stricmp(command1,"t")){
			if(!_stricmp(command2,"to")||!_stricmp(command2,"with"))
				TalkWho(command3);
			else
				TalkWho(command2);
		}
		else if(!strcmp(command1,"map")||!strcmp(command1,"m"))
			drawMap();
		else if(!strcmp(command1,"use")||!strcmp(command1,"u"))
			if(!strcmp(command2,"radio")||!strcmp(command2,"walkie")||!strcmp(command2,"walkie-talkie"))
				if(playerInventory[11]==true && progress==1){
					//TODO make this actually call something.
					progress++;
					cout<<"you tell the guard to stop.\n";
				}
				else if(playerInventory[11]==true){
					cout<<"you only hear static on the other side.\n";
				}
		else if(!strcmp(command1,"disarm")||!strcmp(command1,"deactivate")){}
			//TODO check position and stuff
		else if(!strcmp(command1,"arm")||!strcmp(command1,"activate")){}
			/*if() //TODO position check
				cout<<"Are you crazy? I am not doing that!\n"
			*/
		else
			cout<<"Sorry i didn't understand what you entered.\n";
		waiting=false;
	}
	cout<<endl<<endl;
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

//Outputs the Fifth Gameway logo when the player first starts the game.
void logo(){
	string temp;
	ifstream logo("Assets\\logo.emp");
	while(getline(logo, temp)){
		cout<<temp<<endl;
	}       
	cin.get();
}

//TODO Remove
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

//Outputs the main menu for the player at the beginging of the game.
void mainMenu(){
	string inputString;
	setFirstRun(true);
	system("cls");
	mainMenu:
	string temp;
	ifstream mainMenu("Assets\\mainMenu.emp");
	while(getline(mainMenu, temp)){
		cout<<temp<<endl;
	}

	char * command;
	command = gets_s(userInput);
	if(!_stricmp(command, "new")||!_stricmp(command, "new game")||!_stricmp(command, "n")||!_stricmp(command, "start")||!_stricmp(command, "start new game")||!_stricmp(command, "ne")||!_stricmp(command, "nw")){
		initialise();
		system("cls");
		preface();
		progress=1;
		gameLoop();
	}
	else if(!_stricmp(command, "credits")||!_stricmp(command, "credit")||!_stricmp(command, "c")){
		system("cls");

		string temp;
		ifstream credits("Assets\\credits.emp");
		while(getline(credits, temp)){
			cout<<temp<<endl;
		}

		//system("pause");
		//cin.ignore();
		cin.get();
		system("cls");
		goto mainMenu; //returns the player to the main menu screen.
	}
	else if(!_stricmp(command, "exit")||!_stricmp(command, "quit")||!_stricmp(command, "e")||!_stricmp(command, "q")){
		quitGame();
	}
	else if(!_stricmp(command, "help")||!_stricmp(command, "controls")){
		controls();
		//system("pause");
		cin.get();
		system("cls");
		goto mainMenu;
	}
}

//Outputs the players inventory 
void inventory(){
	cout<<"In your inventory you have:\n\n";

	char comparingID[40]="itemID_XX";
	ifstream itemFile("Assets\\items.emp");
	int failedRuns=0;

	while(!itemFile.eof()){
		char ID[40],itemName[32],description[256];
		itemFile>>ID>>itemName>>description;

		for(int i=0;i<40;i++){
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
				NoSpaces(itemName);

				if(!strcmp(comparingID,ID)){
					cout<<"A "<<itemName<<endl;
					//cout<<"Description: "<<description<<endl;
				}
			}
			else if (playerInventory[i]==false){
				failedRuns++;
				if(failedRuns==39 && i==39)
					cout<<"You have nothing in your inventory :(\n";
			}
		}
	}
	cout<<endl;
}

string nameItem(int num){
	char itemID[40] = "itemID_XX";
	ifstream itemFile("Assets\\items.emp");
	while(!itemFile.eof()){
		char ID[40],itemName[32],description[256];
		itemFile>>ID>>itemName>>description;

		if(num<10){
			itemID[7]='0';
			itemID[8]=num+48;	
		}
		else if(num>=10&&num<20){
			itemID[7]='1';
			itemID[8]=num+38;	
		}
		else if(num>=20&&num<30){
			itemID[7]='2';
			itemID[8]=num+28;	
		}
		else if(num>=30&&num<40){
			itemID[7]='3';
			itemID[8]=num+18;	
		}

		for(int i=0;i<strlen(itemName);i++)
			if(itemName[i]=='_')
				itemName[i]=' ';

		if(!strcmp(itemID,ID))
			return itemName;
	}
	return 0;
}

//Outputs the description for the item, found in the items file.
void describeItem(char item[16]){
	ifstream itemFile("Assets\\items.emp");
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

//Drops the item from the players inventory.
void dropItem(char item[16]){
	if(!strcmp(item,"red"))
		strcpy(item,"red_keycard");
	if(!strcmp(item,"blue"))
		strcpy(item,"blue_keycard");
	if(!strcmp(item,"yellow"))
		strcpy(item,"yellow_keycard");
	ifstream itemFile("Assets\\items.emp");
	while(!itemFile.eof()){
		char ID[40],itemName[32],description[256];
		itemFile>>ID>>itemName>>description;
		
		int numID;

		if(ID[7]=='0')
			numID=ID[8]-48;
		else if(ID[7]=='1')
			numID=ID[8]-38;
		else if(ID[7]=='2')
			numID=ID[8]-28;
		else if(ID[7]=='3')
			numID=ID[8]-18;

		if(!strcmp(item,itemName)){
			cout<<"droping item.\n";
			playerInventory[numID]=false;
		}
	}
}

//TODO Remove
//Not being used except for testing the inventory system.
void giveBox(){
	playerInventory[1]=true;
}

//Prints the controls for the game to the player.
void controls(){
	string temp;
	ifstream controls("Assets\\controls.emp");
	while(getline(controls, temp)){
		cout<<temp<<endl;
	}
}

//TODO Remove
//Not being used, except for testing purposes.
void printRooms(){
	string temp;
	ifstream controls("roommmzzzz.txt");
	while(getline(controls, temp)){
		cout<<temp<<endl;
		//system("pause");
		cin.get();
	}
}

//Removes the '_' from char arrays and replaces them with spaces making it easier for the player to read.
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

//determines what character player is talking to
void TalkWho(char command2[]){
	if(!_stricmp(command2,"Anthony")||!_stricmp(command2,"Parker")){
	bool talkTrue = getTalkPos(1,2,6);
			if(talkTrue){
				int convo1 = 7, convoend = 11;
				Talk(convo1, convoend);
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"Alan")||!_stricmp(command2,"Ford")){
	bool talkTrue = getTalkPos(1,2,7);
			if(talkTrue){
				int convo1 = 12, convoend = 14;
				Talk(convo1, convoend);
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"Samantha")||(!_stricmp(command2,"Weiler"))){
	bool talkTrue = getTalkPos(2,4,8);
			if(talkTrue){
				int convo1 = 15, convoend = 17;
				Talk(convo1, convoend);
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"Jessica")||(!_stricmp(command2,"Creante"))){
	bool talkTrue = getTalkPos(2,6,8);
			if(talkTrue){
				int convo1 = 18, convoend = 20;
				Talk(convo1, convoend);
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"CDC")||(!_stricmp(command2,"GUARD"))){
	bool talkTrue = getTalkPos(3,2,7);
			if(talkTrue){
				int convo1 = 21, convoend = 23;
				Talk(convo1, convoend);
			}
			else{
				cout<<"The "<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"Max")||(!_stricmp(command2,"GOLDSTEIN"))){
	bool talkTrue = getTalkPos(3,3,8);
			if(talkTrue){
				int convo1 = 24, convoend = 26;
				Talk(convo1, convoend);
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"HLC")||(!_stricmp(command2,"GUARD"))){
	bool talkTrue = getTalkPos(4,6,7);
			if(talkTrue){
				int convo1 = 27, convoend = 27;
				Talk(convo1, convoend);
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"Jon")||(!_stricmp(command2,"Ingo"))){
	bool talkTrue = getTalkPos(4,4,6);
			if(talkTrue){
				int convo1 = 28, convoend = 29;
				Talk(convo1, convoend);
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"Dante")||(!_stricmp(command2,"Gaffe"))){
		bool talkTrue = getTalkPos(5,2||3||4,6||7||8);
			if(talkTrue){
				int convo1 = 30, convoend = 30;
				Talk(convo1, convoend);
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"police")||!_stricmp(command2,"officer")||!_stricmp(command2,"cop")){
		bool talkTrue = getTalkPos(5,1,7);
			if(talkTrue){
				int convo1 = 32, convoend = 33;
				Talk(convo1, convoend);
				ending();
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else
		cout<<"Who are you trying to talk to?\n\n";
}


//Quits the gameloop and therfore the game
string quitGame(){
	quit=true;
	return "";
}