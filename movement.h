//Header file for the movement 

#ifndef MOVEMENT_H
#define MOVEMENT_H

void initialise();
void north();
void south();
void east();
void west();
void checkPos();
int checkItemPos();
void changeLevel(char c);
void drawMap();
bool getTalkPos(int a,int b, int c);
void NoSpaces(char thing[]);
bool doorCheck(int a,int b,int c,char d);
int getLevel();
void setFirstRun(bool set);
bool bombCheck();

string nameItem(int num);
void NewLine(char a[]);

//TODO remove both of these.
void drawArray();
void giveBox();

#endif 