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
	char load[32]="Assets/Levels/levelX.emp";
	load[19]=level+48;
	
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
				else if(temp=='C')
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
	char loadItemMap[32]="Assets/Levels/itemMapX.emp";
	loadItemMap[21]=level+48;

	for(int i=0;i<16;i++){	
		for(int j=0;j<16;j++){
			itemPos[i][j]=0;
		}
	}
	
	ifstream itemMap(loadItemMap);
	if(!itemMap){
		cout<<"error opening the file\n";
	}
	while(!itemMap.eof()){
		for(int i=0;i<16;i++){	
			for(int j=0;j<16;j++){
				char temp;
				itemMap>>temp;
				//TODO add all items by their ID tag
				if(temp=='X')
					itemPos[i][j]=0;
				else if(temp=='G')
					itemPos[i][j]=02;
				else if(temp=='C')
					itemPos[i][j]=11;
			}
		}
	}
}

void north(){
	for(int i=0;i<16;i++)
				for(int j=0;j<16;j++)
					if(playerPos[i][j]==1 && playerPos[i-1][j]!=9){
						playerPos[i][j]=0;
						i=i-1;
						playerPos[i][j]=1;
						//cout<<"Player is at "<<i<<" "<<j<<endl;
						//lvl1GameLoop();
						break;
					}
					else if(playerPos[i][j]==1 && playerPos[i-1][j]==9)
						cout<<"You cant go that way!\n";
	checkPos();
}

void south(){
	for(int i=0;i<16;i++)
			for(int j=0;j<16;j++)
				if(playerPos[i][j]==1 && playerPos[i+1][j]!=9){
					playerPos[i][j]=0;
					i=i+1;
					playerPos[i][j]=1;
					break;
				}
				else if(playerPos[i][j]==1 && playerPos[i+1][j]==9)
					cout<<"You cant go that way!\n";
	checkPos();
}

void east(){
	for(int i=0;i<16;i++)
				for(int j=0;j<16;j++)
					if(playerPos[i][j]==1 && playerPos[i][j+1]!=9){
						playerPos[i][j]=0;
						j=j+1;
						playerPos[i][j]=1;
						break;
					}
					else if(playerPos[i][j]==1 && playerPos[i][j+1]==9)
						cout<<"You cant go that way!\n";
	checkPos();
}

void west(){
	for(int i=0;i<16;i++)
			for(int j=0;j<16;j++)
				if(playerPos[i][j]==1 && playerPos[i][j-1]!=9){
					playerPos[i][j]=0;
					j=j-1;
					playerPos[i][j]=1;
					break;
				}
				else if(playerPos[i][j]==1 && playerPos[i][j-1]==9)
					cout<<"You cant go that way!\n";
	checkPos();
}

int checkPos(){
	
	if(playerPos[3][0]==1)
		giveBox();

	char comparingID[16]="roomid_X-X";
	ifstream roomFile("Assets/rooms.emp");
	
	if(!roomFile){
		cout<<"error opening the items.data file\n";
	}
	while(!roomFile.eof()){
		char ID[16],roomName[16],description[256];
		roomFile>>ID>>roomName>>description;

		for(int i=0;i<strlen(description);i++){
			if(description[i]=='_')
				description[i]=' ';
		}

		for(int i=0;i<16;i++)
			for(int j=0;j<16;j++)
				if(playerPos[i][j]==1){
					comparingID[7]=j+48;
					comparingID[9]=i+48;
					if(!strcmp(comparingID,ID)){
						cout<<"you are in "<<roomName<<endl;
						cout<<"Description: "<<description<<endl;
					}
					if(itemPos[i][j]!=0){
						return itemPos[i][j];
					}
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
	if(playerPos[7][7]==1 && level <5 && c=='+'){
		level++;
		initialise();
		cout<<"level changed to level "<<level<<". \n";
	}
	else if(playerPos[7][7]==1 && level>1 && c=='-'){
		level--;
		initialise();
		cout<<"level changed to level "<<level<<". \n";
	}
	
	else
		cout<<"you cannot use the stairs right now.\n";
}

void drawMap(){
	char load[32]="Assets/Levels/levelX.emp";
	load[19]=level+48;
	string temp;
	ifstream controls(load);
	while(getline(controls, temp)){
		cout<<temp<<endl;
	}
}