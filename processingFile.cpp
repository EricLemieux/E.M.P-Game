#include <string>
#include <cstring>
#include<iomanip>
#include <iostream>
#include <fstream>

using namespace std;

#include "processingFile.h"

string itemName[NUMBER_OF_ITEMS];
string itemDescription[NUMBER_OF_ITEMS];
string roomNames[NUMBER_OF_ROOMS];
string roomDoors[NUMBER_OF_ROOMS];
string roomItems[NUMBER_OF_ROOMS];
string roomDescriptions[NUMBER_OF_ROOMS];

int totalItems = 0;
int totalRooms = 0;

bool ProcessItemInfo(string dataLine)
{
string::size_type spos=-1, cpos=-1, len=0;
string dataString="", itemIndexStr="";
int itemIndex = -1;
char token[256];
   
 //  len = dataLine.copy(dataString, dataLine.length, 0);
   dataString.assign(dataLine);

   // get item index value & save in for later ******************************************************************
   if ( (cpos = dataString.find_first_of(":")) != -1 )
   {
      itemIndexStr.assign(dataString,0,cpos);
      spos = itemIndexStr.find_first_of(" "); 
      len = itemIndexStr.copy(token, 3, spos+1);
      token[len]=0;  // or '\0' (null)
      itemIndex = atoi(token);
   }
   else
   {
      cout << "Error Processing Item Info";
      return false;
   }
   dataString = dataString.substr(cpos+1, dataString.length()); // remove the item index info from the dataString



   // get item name & save in item array ******************************************************************
   cpos = -1; // reset
   if ( (cpos = dataString.find_first_of(":")) != -1 ){
		itemName[itemIndex].assign(dataString,0,cpos);
		cout<<"1"<<itemName[itemIndex]<<endl;
   }
   else
   {
      cout << "Error Processing Item Info";
      return false;
   }
   dataString = dataString.substr(cpos+1, dataString.length()); // remove the item name info from the dataString



   // get item description & save in item array ******************************************************************

   cpos = -1; // reset
   if ( (cpos = dataString.find_first_of(":")) != -1 )
      itemDescription[itemIndex].assign(dataString,0,cpos);
   else
   {
      cout << "Error Processing Item Info";
      return false;
   }

   totalItems++;   // tally up another item
   return true;
}

bool ProcessRoomInfo(string dataString)
{
   return true;
}


void SaveItemData(char *outfileName)
{
ofstream outFile(outfileName);


   for (int i = 0; i < totalItems; i++)
   {
      outFile << "item " << i << ":" << itemName[i] << ":" << itemDescription[i] << ":\n" ;
   }
   outFile << flush;
   outFile.close();

}