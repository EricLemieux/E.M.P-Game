#include <iostream>
#include <fstream>
using namespace std;

#include "movement.h"

int playerPos[7][7];

void initialise(){
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			playerPos[i][j]=0;
	playerPos[1][0]=1;//initialises the player's starting position.
	cout<<"initialised\n";
}

void north(){
	for(int i=0;i<5;i++)
				for(int j=0;j<5;j++)
					if(playerPos[i][j]==1 && i>0){
						playerPos[i][j]=0;
						i=i-1;
						playerPos[i][j]=1;
						cout<<"Player is at "<<i<<" "<<j<<endl;
						//lvl1GameLoop();
						break;
					}
					else if(playerPos[i][j]==1&&j<=0)
					cout<<"You cant go that way!\n";
	checkPos();
}

void south(){
	for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				if(playerPos[i][j]==1 && i<5){
					playerPos[i][j]=0;
					i=i+1;
					playerPos[i][j]=1;
					cout<<"Player is at "<<i<<" "<<j<<endl;
					break;
				}
				else if(playerPos[i][j]==1&&i>=5)
					cout<<"You cant go that way!\n";//TODO fix this error message.
	checkPos();
}

void east(){
	for(int i=0;i<5;i++)
				for(int j=0;j<4;j++)
					if(playerPos[i][j]==1 && j<=4){
						playerPos[i][j]=0;
						j=j+1;
						playerPos[i][j]=1;
						cout<<"Player is at "<<i<<" "<<j<<endl;
						break;
					}
					else if(playerPos[i][j]==1 && i>=3)
						cout<<"You cant go that way!\n";//TODO Fix this error message.
	checkPos();
}

void west(){
	for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
				if(playerPos[i][j]==1 && j>0){
					playerPos[i][j]=0;
					j=j-1;
					playerPos[i][j]=1;
					cout<<"Player is at "<<i<<" "<<j<<endl;
					break;
				}
				else if(playerPos[i][j]==1&&j<=0)
					cout<<"You cant go that way!\n";
	checkPos();
}

void checkPos(){
	char comparingID[16]="roomid_X-X";
	ifstream roomFile("rooms.emp");
	
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

	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if(playerPos[i][j]==1){
				comparingID[7]=j+48;
				comparingID[9]=i+48;
				cout<<comparingID<<endl;
				if(!strcmp(comparingID,ID)){
					cout<<"you are in "<<roomName<<endl;
					cout<<"Description: "<<description<<endl;
				}
			}
	}
}