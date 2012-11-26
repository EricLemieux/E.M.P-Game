//E.M.P
//Created by Fith Gateway Games

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <windows.h>

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
void Computer();
void HackPassword(char answer[], int Level);
bool HackMiniGame(int Level);
void BootComp();
void MenuComp(char name[], int personID);
bool Keypad();
void EmailComp(char name[]);

bool quit=false;
char userInput[64];
char command1[NUM], command2[NUM], command3[NUM];
bool playerInventory[64];
int progress=0;
int bossHP=3;

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
					changeLevel('+');
			}
			else if(!_stricmp(command2, "up")||!_stricmp(command2, "u"))
					changeLevel('-');
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
		else if(!_stricmp(command1, "open")||!_stricmp(command1, "o")){
			if(!_stricmp(command2, "door")||!_stricmp(command2, "d")||!_stricmp(command3, "door")){
				if(doorCheck(1,2,7,'e'))
					if(playerInventory[13]){
						cout<<"Door opened.\n";
						east();
					}
					else
						cout<<"This door appears to be locked.\n";
				else if(doorCheck(2,3,7,'w')){
					bool keycode = Keypad();
					if(keycode){
						cout<<"Door opened.\n";
						west();
					}
					else
						cout<<"Nope.\n";
				}
				else if(doorCheck(4,7,7,'w')){
					if(playerInventory[13] && playerInventory[27] && playerInventory[28]){
						if(progress==2){
							cout<<"Door opened.\n";
							west();
						}
						else if(progress!=2){
							cout<<"As you enter the room the guard spots you and shoots you.\n You are now dead.\n";
							//gameOver();//TODO CATS
						}
					}
					else
						cout<<"This door appears to need three keys to unlock.\n";
				}
				else if(doorCheck(5,7,7,'w')){
					if(progress==3){
						progress=4;
						cout<<"Door opened.\n";
						west();
					}
					else
						cout<<"Nope.\n";
				}
				else if(doorCheck(5,2,7,'w')){
					if(progress==5){
						progress=6;
						cout<<"Door opened.\n";
						west();
					}
					else
						cout<<"Dante is still standing behind you!\n";
				}
			}
			else
				cout<<"what would you like to open?\n";
		}
		else if(!_stricmp(command1,"describe")||!_stricmp(command1,"view")||!_stricmp(command1,"examine"))
			describeItem(command2);
		else if(!strcmp(command1,"drop"))
			dropItem(command2);
		else if(!strcmp(command1,"grab")||!strcmp(command1,"pick")||!strcmp(command1,"take")){
			int temp = checkItemPos('-');
			if(temp!=0){
				playerInventory[temp]=true;
				cout<<endl<<"You picked up a "<<nameItem(temp);
			}
		}
		else if(!_stricmp(command1,"talk")||!_stricmp(command1,"t")||!_stricmp(command1,"speak")||!_stricmp(command1,"tell")){
			if(!_stricmp(command2,"to")||!_stricmp(command2,"with"))
				TalkWho(command3);
			else
				TalkWho(command2);
		}
		else if(!strcmp(command1,"map")||!strcmp(command1,"m"))
			drawMap();
		else if(!strcmp(command1,"use")||!strcmp(command1,"u")){
			if(!strcmp(command2,"radio")||!strcmp(command2,"walkie")||!strcmp(command2,"walkie-talkie"))
				if(playerInventory[11]==true && progress==1){
					//TODO make this actually call something.
					progress=2;
					cout<<"CLAYTON_HAECKER says: \"You can take your break, I will take guard duty\".\n";
					cout<<"GUARD says: \"Thanks man, make sure the hostages upstairs dont get out\".\n";
				}
				else if(playerInventory[11]==true){
					cout<<"you only hear snoring on the other side.\n";
				}
				else if(playerInventory[11]==false){
					cout<<"You dont have one of those.\n";
				}
		}
		else if(!_stricmp(command1,"Computer")||!_stricmp(command1,"c")||!_stricmp(command1,"hack")||!_stricmp(command2,"Computer")){
			if(getLevel()!=5)
				Computer();
			else if(bossCheck() && bossHP>0){
				if(HackMiniGame(getLevel()-bossHP)){
					bossHP--;
					Talk(36-bossHP, 36-bossHP);
					if(bossHP==0){
						progress=5;
						setPos(7,3,0);
						cout<<"Dante Has been defeated.\n";
					}
				}
				else
					bossHP=bossHP;
			}
		}
		else if(!strcmp(command1,"disarm")||!strcmp(command1,"deactivate")){
			if(bombCheck() && progress==2){
				if(HackMiniGame(getLevel())){
					cout<<"Bomb disarmed.\n";
					progress=3;
				}
			}
			else
				cout<<"You cant do that here...\n";
		}
		else if(!strcmp(command1,"arm")||!strcmp(command1,"activate"))
			if(bombCheck())
				cout<<"Are you crazy? I am not doing that!\n";
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
		Sleep(75);
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
	else if(!_stricmp(command, "help")||!_stricmp(command, "controls")||!_stricmp(command, "c")){
		controls();
		//system("pause");
		//cin.get();
		cin.ignore();
		system("cls");
		goto mainMenu;
	}
	else{
		cout<<"Sorry I dont understand what you entered.\n";
		cin.ignore();
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
	if(!_stricmp(item,"red"))
		strcpy(item,"red_keycard");
	else if(!_stricmp(item,"blue"))
		strcpy(item,"blue_keycard");
	else if(!_stricmp(item,"yellow"))
		strcpy(item,"yellow_keycard");

	ifstream itemFile("Assets\\items.emp");
	while(!itemFile.eof()){
		char ID[40],itemName[32],description[256];
		itemFile>>ID>>itemName>>description;

		NoSpaces(description);
		NewLine(description);
		
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

//Creates line breaks by replacing '$' with '\n'
void NewLine(char a[]){
	for(int i=0; i<strlen(a); i++){
		if(a[i] == '$')
		a[i] = '\n';
	}
}

void Apostrophe(char thing[]){
	for(int i=0;i<strlen(thing);i++){
		if(thing[i]=='#')
		thing[i]='\'';
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
		ifstream Dialog("Assets\\Story\\talk.emp");
		if(!Dialog){
			cout<<"error opening the talk.emp file\n";
		}
		while(!Dialog.eof()){
			char dialog[256], character[64], talkpin[15];
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
	bool talkTrue = getTalkPos(4,6,6);
			if(talkTrue){
				int convo1 = 27, convoend = 27;
				Talk(convo1, convoend);
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"Jon")||(!_stricmp(command2,"Ingo"))){
	bool talkTrue = getTalkPos(4,6,6);
			if(talkTrue){
				int convo1 = 28, convoend = 30;
				Talk(convo1, convoend);
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"Dante")||(!_stricmp(command2,"Gaffe"))){
		bool talkTrue = getTalkPos(5,2||3||4,6||7||8);
			if(talkTrue){
				int convo1 = 31, convoend = 33;
				Talk(convo1, convoend);
			}
			else{
				cout<<command2<<command3<<" isn't here... \n\n";
			}
	}else if(!_stricmp(command2,"police")||!_stricmp(command2,"officer")||!_stricmp(command2,"cop")){
		bool talkTrue = getTalkPos(5,1,7);
			if(talkTrue){
				int convo1 = 37, convoend = 39;
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

//Computer Access function, determines who's computer it is being accessed
void Computer(){
	bool hacked = false, Compute;
	int level = getLevel(), personID = 1, p;
	char name[64] = " ";

	for(p=1; p<=11; p++){
		switch(p){
		case 1:
			Compute = getTalkPos(1,6,5);
			if(Compute){
				strcat_s(name,"FloorCleaning");
			}break;
		case 2:
			Compute = getTalkPos(1,5,9);
			if(Compute){
				strcat_s(name,"FloorCleaning");
			}break;
		case 3:
			Compute = getTalkPos(2,3,6);
			if(Compute){
				strcat_s(name,"AnthonyParker");
			}break;
		case 4:
			Compute = getTalkPos(2,8,4);
			if(Compute){
				strcat_s(name,"SamanthaWeiler");
			}break;
		case 5:
			Compute = getTalkPos(2,5,6);
			if(Compute){
				strcat_s(name,"ClaytonHaecker");
			}break;
		case 6:
			Compute = getTalkPos(2,2,8);
			if(Compute){
				strcat_s(name,"MaxGoldstein");
			}break;
		case 7:
			Compute = getTalkPos(3,5,6);
			if(Compute){
				strcat_s(name,"JessicaCreante");
			}break;
		case 8:
			Compute = getTalkPos(3,5,8);
			if(Compute){
				strcat_s(name,"ThomasHobbs");
			}break;
		case 9:
			Compute = getTalkPos(3,3,6);
			if(Compute){
				personID = 2;
			}break;
		case 10:
			Compute = getTalkPos(4,5,4);
			if(Compute){
				personID = 3;
			}break;
		}
		if(Compute){
			hacked = HackMiniGame(level);
			if(hacked){
				MenuComp(name, personID);
				//return;
			}
		}
		if(p == 11){
			cout<<"\nThere's no computer here to use.\n\n";
		}
	}
}

//Print potential passwords to screen and sends random password to HackMiniGame function
void HackPassword(char answer[], int Level){
	char random[10] = {'!','@','$','%','?','(',')','&','*'};
	char lettercode[21] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'};
	char lineCode[3], holder;
	int swap1, swap2;


	for(int i=0; i<=30; i++){ //Randomize lettercodes
		swap1=rand()%20;
		swap2=rand()%20;
		holder = lettercode[swap1];
		lettercode[swap1] = lettercode[swap2];
		lettercode[swap2] = holder;
	}

	holder=10;
	cout<<"Password needed...attempting system override... \n";
	cout<<"...possible passwords solutions...";
	for(int i=0; i<=250; i++){//Print hack code and randomize
		swap1 = rand()%10;
		if(swap1 != 9){//Print random character
			cout<<random[swap1];
		}else if(holder != -1){//Print first 10 randomized code words
			lineCode[0] = Level + 48;
			lineCode[1] = lettercode[holder];
			lineCode[2] = '\0';
			holder--;
			ifstream Comphack("Assets\\hack.emp");
			if(!Comphack){
				cout<<"error opening the items.data file\n";
			}
			while(!Comphack.eof()){
			char word[10], text[3];
			Comphack>>text>>word; 
				if (!strcmp(lineCode,text)){
					cout<<"[_"<<word<<"_]";
				}
			}
		}
	}

	//choose random word from first 10 code words as answer
	lineCode[1] = lettercode[rand()%10];
	ifstream Comphack("Assets/hack.emp");
	if(!Comphack){
		cout<<"error opening the items.data file\n";
	}
	while(!Comphack.eof()){
		char text[3];
		Comphack>>text>>answer; 
		if (!strcmp(lineCode,text)){
				break;
		}
	}
}

//Needs input of difficulty corresponding to level 1-5, plays the guess game
bool HackMiniGame(int Level){
	char answer[10], guess[10];
	int right, gright = 0;

	HackPassword(answer, Level);

	cout<<"\nENTER PASSWORD\n";
	//3 guesses
	for(int k=3; k>=0; k--){ //k is number of attempts
		cin.getline(guess,10);
		for(int i=0; i<=Level+2; i++){
			guess[i] = toupper(guess[i]);
		}
		right = strcmp(answer,guess); //if guess is right, return true, allow next attempt if false
		if(right == 0){
			cout<<"PASSWORD ACCEPTED\n";
			return true;
		}
		for(int i=0; guess[i]!='\0'; i++){
			if(guess[i] == answer[i]){
				gright++;
			}
		}
		cout<<"Letters matched "<<gright<<endl;
		cout<<k<<" attempts left before system lockout \n";
		cout<<answer<<"     DEBUG ANSWER"<<endl; //TODO//remove this DEBUG <----------------------=====================================
	}
	cout<<"ERROR: INCORRECT PASSWORD\nLOGGING OUT\n";
	return false;
}

//Printed when player first accesses a computer
void BootComp(){
	int i, a;

	for(a=1; a<=5; a++){
		if((a == 1)||(a == 5)){
			for(i=1; i<=80; i++){
				if((i==1)||(i==80))
					cout<<"+";
				else
					cout<<"-";
			}
		}
		if((a == 2)||(a == 4)){
			for(i=1; i<=80; i++){
				if((i == 1)||(i == 80))
					cout<<"|";
				else
					cout<<" ";
			}
		}
		if(a == 3){
			for( i=1; i<=25; i++){
				if((i == 1)||(i == 25))
					cout<<"|";
				else if(i == 16)
					cout<<"CARDINAL DATA CENTER TERMINAL -- MASS NET LINK DISABLED ";
				else
					cout<<" ";
			}
		}
	}
	cout<<"All rights reserved 2055. \n\n";
}

//Menu commands for computer, 3 events for 1normal PC, 2security comp terminal (advances plot progress to 2), 3 is bomb deactivation (advances plot progress to 4)
void MenuComp(char name[], int personID){//change person to person ID
	int k = 1;
	char COMPcommand = ' ';
	bool quit = false;

	BootComp();

	if (personID == 1)
		cout<<endl<<"Welcome user"<<name<<" \n\n";
	do{
		cout<<"MAIN MENU \n\n";
		if (personID == 1)
			cout<<" [E]mail \n"; //typical computers, for character emails
		if (personID == 2)
			cout<<" [S]ecurity Cameras \n [C]hronological Event Detail Report \n"; //security desk, activating cameras
		if (personID == 3)
			cout<<" Unrecognized External Access Detected: code"<<rand()%100000+10000<<" \n [A]ccess foreign entity \n"; //for hacking bomb
		cout<<" [H]elp \n [Q]uit";
		if(k == 1)
			for(k=1; k<=6; k++){
				cout<<"\n";	
			}

		cout<<"\n\nEnter Command:";
		cin>>COMPcommand;
		if((COMPcommand == 'h')||(COMPcommand == 'H')){
			cout<<"\nType the first letter of a menu command to access that command.  To access \n[E]mail type 'E'.  'Q' is to quit interface.  To access commands preceded by a \nnumber, type the number. To access [1]FirstE-mail, type 1. \n\n";
		}else if((COMPcommand == 'E')||(COMPcommand == 'e')){
			if (personID == 1);		
			EmailComp(name);
		}else if((COMPcommand == 'C')||(COMPcommand == 'c')){
			if(personID == 2){
				cout<<"0700: An employee enters the Cardinal Data Center (CDC). He is followed by another carrying a bag.\n0710: The employee greets the security guard and enters the elevator. The man following guns down the security guard and moves the body. The CDC’s security is compromised.\n0730: The gunman returns to the security post in a security guard uniform.\n0735: The CDC’s freight door is opened, a large vehicle enters. Three persons enter the CDC through the front.\n0730-0800: Eight employees enter the building.\n0805: The building’s security system is trigger. The building is locked down.\n0815: The press are contacted about an EMP within the CDC. A radical neo-Luddite organization issues a manifesto and declares every hour a demand will be made.\n0845: Police lock down the surrounding areas. An evacuation takes place.\n0900: First Demand: Remove police snipers, every rebel agent has a “dead-man trigger”. If one dies the EMP will be detonated.\n0930: Police become aware of multiple hostages inside the CDC.\n1000: Second demand was not made. Police attempt contact.\n";
			system("pause");}
		}else if((COMPcommand == 'S')||(COMPcommand == 's')){
			if(personID == 2){
				//if(progress <= 2)
					//progress++;
					//cout<<   Enter plot develpment for act2, declaring where bomb is
				//else
					cout<<"You see a guard sitting on a chair, playing with a walkie-talkie, he is armed a large gun.";
			}
		}else if((COMPcommand == 'A')||(COMPcommand == 'a')){
			if(personID == 3){
				//somebool = Hack(Level);
			}
		}else if((COMPcommand == 'Q')||(COMPcommand == 'q')){
			quit = true;
			cout<<"Logging Off...\n\n\n";
			cin.ignore();
			//CheckPos();
		}else{
			cout<<"\nVALID COMMAND NOT ENTERED\n\n";
		}
	}while(!quit);
}

//The keypad puzzle for the second floor head office.
bool Keypad(){
	char code[5] = "1337", guess[32];

	string temp;
	ifstream controls("Assets\\keypad.emp");
	while(getline(controls, temp)){
		cout<<temp<<endl;
	}

	cout<<"\nENTER CODE: ";
	cin.getline(guess,32);
	if(!strcmp(guess, code)){
		cout<<"\nACCESS GRANTED\n";
		return 1;
	}else{
		cout<<"\nACCESS DENIED\n";
		return 0;
	}
}

//imports e-mails appropriate to the computer the plyer is on, and allows the player to choose and print emails to read
void EmailComp(char name[]){
	char subject1[64] = ":", subject2[64] = ":", subject3[64] = ":";
	bool back = false;

	switch(name[1]){
	case 'A':
		strcat(subject1,"SPAM");
		strcat(subject2,"Regarding_Goldstein");
		strcat(subject3,"Try_GRUE_game");
		break;
	case 'M':
		strcat(subject1,"US");
		strcat(subject2,"XXX-HOTLIVEGIRLS-XXX(SPAM)");
		strcat(subject3,"RE:SPAM");
		break;
	case 'S':
		strcat(subject1,"Concerning_Cafeteria_Microwave");
		strcat(subject2,"RE:Regarding_Goldstein");
		strcat(subject3,"Can_I_has_Access?");
		break;
	case 'C':
		strcat(subject1,"Concerning_Cafeteria_Microwave");
		strcat(subject2,"All_Staff");
		strcat(subject3,"I_Know");
		break;
	case 'J':
		strcat(subject1,"Concerning_Cafeteria_Microwave");
		strcat(subject2,"All_Staff");
		strcat(subject3,"PLAN");
		break;
	case 'T':
		strcat(subject1,"Concerning_Cafeteria_Microwave");
		strcat(subject2,"All_Staff");
		strcat(subject3,"Try_GRUE_game");
		break;
	case 'F':
		strcat(subject1,"Concerning_Cafeteria_Microwave");
		strcat(subject2,"All_Staff");
		strcat(subject3,"Clean-up");
		break;
	}



	do{
		char input;
		cout<<"\nEmail Menu\n\n [1]"<<subject1<<"\n [2]"<<subject2<<"\n [3]"<<subject3<<"\n [B]ACK\n\nENTER COMMAND:";
		cin>>input;
		if((input == 'b')||(input == 'B')){
			back = true;
			break;
		}
		ifstream Email("Assets\\email.emp");
		if(!Email){
			cout<<"error opening the items.data file\n";
		}
		while(!Email.eof()){
			char subject[64], message[1024], header[128];
			Email>>subject>>header>>message;
			NewLine(header);
			NoSpaces(header);
			NoSpaces(message);
			Apostrophe(header);
			Apostrophe(message);
			switch(input){
			case '1':
					if(!strcmp(subject,subject1)){
						NoSpaces(subject);
						cout<<"\nTo:"<<name<<header<<subject<<endl<<message<<endl<<endl;
					}
				break;
			case '2':
					if(!strcmp(subject,subject2)){
						NoSpaces(subject);
						cout<<"\nTo:"<<name<<header<<subject<<endl<<message<<endl<<endl;
					}
				break;
			case '3':
					if(!strcmp(subject,subject3)){
						NoSpaces(subject);
						cout<<"\nTo:"<<name<<header<<subject<<endl<<message<<endl<<endl;
					}
				break;
			default:
				cout<<"\nNOT A VALID INPUT\n\n";
				break;
			}
		}
	}while(back == false);
}

int getProgress(){
	return progress;
}