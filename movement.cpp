#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

#include "movement.h"

int playerPos[16][16];
int level=1;

void initialise(){
	/*for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			playerPos[i][j]=0;
	playerPos[1][0]=1;//initialises the player's starting position.
	cout<<"initialised\n";*/

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
					//cout<<"Player is at "<<i<<" "<<j<<endl;
					break;
				}
				else if(playerPos[i][j]==1 && playerPos[i+1][j]==9)
					cout<<"You cant go that way!\n";//TODO fix this error message.
	checkPos();
}

void east(){
	for(int i=0;i<16;i++)
				for(int j=0;j<16;j++)
					if(playerPos[i][j]==1 && playerPos[i][j+1]!=9){
						playerPos[i][j]=0;
						j=j+1;
						playerPos[i][j]=1;
						//cout<<"Player is at "<<i<<" "<<j<<endl;
						break;
					}
					else if(playerPos[i][j]==1 && playerPos[i][j+1]==9)
						cout<<"You cant go that way!\n";//TODO Fix this error message.
	checkPos();
}

void west(){
	for(int i=0;i<16;i++)
			for(int j=0;j<16;j++)
				if(playerPos[i][j]==1 && playerPos[i][j-1]!=9){
					playerPos[i][j]=0;
					j=j-1;
					playerPos[i][j]=1;
					//cout<<"Player is at "<<i<<" "<<j<<endl;
					break;
				}
				else if(playerPos[i][j]==1 && playerPos[i][j-1]==9)
					cout<<"You cant go that way!\n";
	checkPos();
}

void checkPos(){
	
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
					//cout<<comparingID<<endl;
					if(!strcmp(comparingID,ID)){
						cout<<"you are in "<<roomName<<endl;
						cout<<"Description: "<<description<<endl;
					}
				}
	}
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
		cout<<"level changed.\n";
	}
	else if(playerPos[7][7]==1 && level>1 && level <5 && c=='-'){
		level--;
		initialise();
		cout<<"level changed.\n";
	}
	
	else
		cout<<"you cannot use the stairs right now.\n";
}