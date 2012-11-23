//Header file for the movement 

#ifndef MOVEMENT_H
#define MOVEMENT_H

void initialise();
void north();
void south();
void east();
void west();
int checkPos();
void changeLevel(char c);
void drawMap();
bool getTalkPos(int a,int b, int c);
void NoSpaces(char thing[]);

void drawArray();

void giveBox();

#endif 