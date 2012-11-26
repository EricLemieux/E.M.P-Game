#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

#include "movement.h"

int playerPos[16][16];
int itemPos[16][16];
int level=1;
bool firstRun=true;

void initialise(){
	//Initialising the players position using the map files.
	char load[32]="Assets\\Levels\\levelX\\levelX.emp";
	load[19]=level+48;
	load[26]=level+48;
	
	ifstream map1(load);
	while(!map1.eof()){
		for(int i=0;i<16;i++){	
			for(int j=0;j<16;j++){
				char temp;
				map1>>temp;
				
				if(temp=='X')
					playerPos[i][j]=9;
				else if(temp=='O')
					playerPos[i][j]=0;
				else if(temp=='P')
					playerPos[i][j]=1;
				else if(temp=='D')
					playerPos[i][j]=5;
			}
		}
	}
	
	if(firstRun){
		playerPos[7][7]=0;
		playerPos[6][1]=1;
	}
	firstRun=false;
	
	//Loading the item map for the positions of the items at the begining of the game.
	char loadItemMap[40]="Assets\\Levels\\levelX\\itemMapX.emp";
	loadItemMap[19]=level+48;
	loadItemMap[28]=level+48;

	for(int i=0;i<16;i++){	
		for(int j=0;j<16;j++){
			itemPos[i][j]=0;
		}
	}
	
	ifstream itemMap(loadItemMap);
	if(!itemMap){
		cout<<"error opening the item map file\n";
	}
	while(!itemMap.eof()){
		for(int i=0;i<16;i++){	
			for(int j=0;j<16;j++){
				char temp;
				itemMap>>temp;
				if(temp=='X'||temp=='0')
					itemPos[i][j]=0;
				else if(temp=='L')//Laser handcuffs
					itemPos[i][j]=1;
				else if(temp=='P')//portrait
					itemPos[i][j]=2;
				else if(temp=='D')//door
					itemPos[i][j]=3;
				else if(temp=='l')//lamp
					itemPos[i][j]=4;
				else if(temp=='T')//table
					itemPos[i][j]=5;
				else if(temp=='S')//security camera
					itemPos[i][j]=6;
				else if(temp=='A')//anthony parker
					itemPos[i][j]=7;
				else if(temp=='a')//alan ford
					itemPos[i][j]=8;
				else if(temp=='s')//samantha weiler
					itemPos[i][j]=9;
				else if(temp=='B')//box
					itemPos[i][j]=10;
				else if(temp=='W')//walkie talkie
					itemPos[i][j]=11;
				else if(temp=='$')//screwdriver
					itemPos[i][j]=12;
				else if(temp=='R')//red keycard
					itemPos[i][j]=13;
				else if(temp=='C')//couch
					itemPos[i][j]=14;
				else if(temp=='t')//tv
					itemPos[i][j]=15;
				else if(temp=='F')//fridge
					itemPos[i][j]=16;
				else if(temp=='I')//inside fridge
					itemPos[i][j]=17;
				else if(temp=='i')//inside bag
					itemPos[i][j]=18;
				else if(temp=='M')//microwave
					itemPos[i][j]=19;
				else if(temp=='w')//window
					itemPos[i][j]=20;
				else if(temp=='c')//computer terminal
					itemPos[i][j]=21;
				else if(temp=='d')//door
					itemPos[i][j]=22;
				else if(temp=='#')//desk
					itemPos[i][j]=23;
				else if(temp=='O')//office supplies
					itemPos[i][j]=24;
				else if(temp=='%')//desk
					itemPos[i][j]=25;
				else if(temp=='Z')//drawer
					itemPos[i][j]=26;
				else if(temp=='b')//blue keycard
					itemPos[i][j]=27;
				else if(temp=='Y')//yellow keycard
					itemPos[i][j]=28;
				else if(temp=='E')//desk
					itemPos[i][j]=29;
				else if(temp=='!')//Telephone
					itemPos[i][j]=30;
				else if(temp=='H')//HLC gun
					itemPos[i][j]=31;
				else if(temp=='G')//big guard
					itemPos[i][j]=32;
				else if(temp=='o')//omonous door
					itemPos[i][j]=33;
				else if(temp=='h')//HLC laser handcuffs
					itemPos[i][j]=34;
				else if(temp=='m')//mind control device
					itemPos[i][j]=35;
				else if(temp=='e')//EMP bomb
					itemPos[i][j]=36;
				else if(temp=='f')//BFG
					itemPos[i][j]=37;
			}
		}
	}
}

void north(){
	for(int i=0;i<16;i++)
				for(int j=0;j<16;j++)
					if(playerPos[i][j]==1 && playerPos[i-1][j]==0){
						playerPos[i][j]=0;
						i=i-1;
						playerPos[i][j]=1;
						checkPos();
						//cout<<"Player is at "<<i<<" "<<j<<endl;
						//lvl1GameLoop();
						break;
					}
					else if(playerPos[i][j]==1 && playerPos[i-1][j]==9)
						cout<<"There is a wall there.\n";
					else if(playerPos[i][j]==1 && playerPos[i-1][j]==5)
						cout<<"you have to open the door before you can walk through it.\n";
}

void south(){
	for(int i=0;i<16;i++)
			for(int j=0;j<16;j++)
				if(playerPos[i][j]==1 && playerPos[i+1][j]==0){
					playerPos[i][j]=0;
					i=i+1;
					playerPos[i][j]=1;
					checkPos();
					break;
				}
				else if(playerPos[i][j]==1 && playerPos[i+1][j]==9)
					cout<<"There is a wall there!\n";
				else if(playerPos[i][j]==1 && playerPos[i+1][j]==5)
					cout<<"you have to open the door before you can walk through it.\n";
}

void east(){
	for(int i=0;i<16;i++)
				for(int j=0;j<16;j++)
					if(playerPos[i][j]==1 && playerPos[i][j+1]==0){
						playerPos[i][j]=0;
						j=j+1;
						playerPos[i][j]=1;
						checkPos();
						break;
					}
					else if(playerPos[i][j]==1 && playerPos[i][j+1]==9)
						cout<<"There is a wall there!\n";
					else if(playerPos[i][j]==1 && playerPos[i][j+1]==5)
						cout<<"You have to open the door before you can walk through it.\n";
}

void west(){
	for(int i=0;i<16;i++)
			for(int j=0;j<16;j++)
				if(playerPos[i][j]==1 && playerPos[i][j-1]==0){
					playerPos[i][j]=0;
					j=j-1;
					playerPos[i][j]=1;
					checkPos();
					break;
				}
				else if(playerPos[i][j]==1 && playerPos[i][j-1]==9)
					cout<<"There is a wall there!\n";
				else if(playerPos[i][j]==1 && playerPos[i][j-1]==5)
					cout<<"You have to open the door before you can walk through it.\n";
}

void checkPos(){
	char comparingID[16]="roomX_X_X";
	char fileName[40]="Assets\\Levels\\LevelX\\levelXrooms.emp";
	fileName[19]=level+48;
	fileName[26]=level+48;
	ifstream roomFile(fileName);
	if(!roomFile){
		cout<<"error opening the items.data file\n";
	}
	for(int i=0;i<16;i++)
			for(int j=0;j<16;j++)
				if(playerPos[i][j]==1){
					comparingID[4]=level+48;
					comparingID[6]=i+48;
					comparingID[8]=j+48;
				}

	//cout<<comparingID<<endl;
	while(!roomFile.eof()){
		char ID[16],roomName[32],description[512];
		roomFile>>ID>>roomName>>description;

		NoSpaces(roomName);
		NoSpaces(description);
		NewLine(description);

		if(!strcmp(comparingID,ID)){
						cout<<"you are in "<<roomName<<endl;
						cout<<"Description: "<<description<<endl;
					}
	}
	checkItemPos(' ');
}

int checkItemPos(char sym){
	//loops through the player position array and checks to see if an item and the player are in the same location.
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
			if(playerPos[i][j]==1){					
				if(itemPos[i][j]!=0){
					if(sym!='-')
						cout<<"You see a "<<nameItem(itemPos[i][j])<<"."<<endl;
					return itemPos[i][j];//Returns back what item the player is standing on.
				}
			}
	return 0; 
}

//Not being used.
void drawArray(){
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
			cout<<i<<"-"<<j<<" : "<<playerPos[i][j]<<endl;
}

void changeLevel(char c){
	if(playerPos[7][7]==1 && level <5 && c=='-'){
		level++;
		initialise();
		checkPos();
		//cout<<"level changed to level "<<level<<". \n";
	}
	else if(playerPos[7][7]==1 && level>1 && c=='+'){
		level--;
		initialise();
		checkPos();
	}
	
	else
		cout<<"you cannot use the stairs right now.\n";
}

void drawMap(){
	char load[32]="Assets\\Levels\\levelX\\levelX.emp";
	load[19]=level+48;
	load[26]=level+48;
	string temp;
	ifstream map(load);
	if(!map)
		cout<<"error opening map file\n";
	while(getline(map, temp)){
		cout<<temp<<endl;
	}
}

bool getTalkPos(int a,int b,int c){
	if(level==a && playerPos[c][b]==1)
		return true;
	else 
		return false;
}

bool doorCheck(int a,int b,int c,char d){
	if(level==a && playerPos[c][b]==1){
		if(d=='e')
			playerPos[c][b+1]=0;
		else if(d=='w')
			playerPos[c][b-1]=0;
		else if(d=='n')
			playerPos[c-1][b]=0;
		else if(d=='s')
			playerPos[c+1][b]=0;
		return true;
	}
	return false;
}

bool bombCheck(){
	if(level==4 && playerPos[5][5]==1){
		return true;
	}
	return false;
}

int getLevel(){
	return level;
}

void setFirstRun(bool set){
	firstRun=set;
}