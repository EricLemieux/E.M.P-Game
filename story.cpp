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
