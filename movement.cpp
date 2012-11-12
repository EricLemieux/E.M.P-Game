#include <iostream>
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
}