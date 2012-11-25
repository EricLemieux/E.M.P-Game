#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "story.h"

void preface(){
	string temp;
	ifstream preface("Assets/Story/preface.emp");
	while(getline(preface, temp)){
		cout<<temp<<endl;
	}
}

void ending(){
	string temp;
	ifstream ending("Assets/Story/ending.emp");
	while(getline(ending, temp)){
		cout<<temp<<endl;
	}
	cin.get();
	//quitGame();
	mainMenu();
}
