//Header file for the movement 

#ifndef MOVEMENT_H
#define MOVEMENT_H

void initialise();
void north();
void south();
void east();
void west();
void checkPos();
int checkItemPos(char sym);
void changeLevel(char c);
void drawMap();
bool getTalkPos(int a,int b, int c);
void NoSpaces(char thing[]);
void openDoor(int a,int b,char c);
bool doorCheck(int a,int b,int c,char d);
int getLevel();
void setFirstRun(bool set);
bool bombCheck();
bool bossCheck();
int getPos();
void setPos(int a,int b,int c);
void setItemPos(int itemID, char order);
//bool bossClose(int a,int b);

string nameItem(int num);
void NewLine(char a[]);
int getProgress();

//TODO remove both of these.
void drawArray();
void giveBox();

#endif 