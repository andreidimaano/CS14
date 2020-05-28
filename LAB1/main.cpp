//main provided by LePendu
//cindy ho helped me understand what change pos was
#include <iostream>
#include <iomanip>
//https://www.cplusplus.com/reference/iomanip/

using namespace std;

#include "Playlist.h"

void PrintMenu(const string playlistTitle);

int main() 
{
   string playlistTitle;
   // Prompt user for playlist title
   cout << "Enter playlist's title:";
   getline(cin, playlistTitle);
   cout << endl << endl;
   // Output play list menu options
   PrintMenu(playlistTitle);
   return 0;
}

void PrintMenu(const string playlistTitle) 
{
   char menuOp = ' ';
   string uniqueID;
   string songName;
   string artistName;
   int songLength = 0;
   int numNodes = 0;
   int songPosition = 0;
   int newPosition = 0;
   int totalTime;
   PlaylistNode* newSong = 0;
   PlaylistNode* currNode = 0;
   PlaylistNode* songNode = 0;
   PlaylistNode* prevNode = 0;
   PlaylistNode* insertPosNode = 0;
   PlaylistNode* headNode = 0;
   PlaylistNode* tailNode = 0;
   PlaylistNode* currPrintNode = 0;
   // Output menu option, prompt users for valid selection
   while(menuOp != 'q') 
   {
      menuOp = ' ';
      cout << playlistTitle << " PLAYLIST MENU" << endl;
      cout << "a - Add song" << endl;
      cout << "d - Remove song" << endl;
      cout << "c - Change position of song" << endl;
      cout << "s - Output songs by specific artist" << endl;
      cout << "t - Output total time of playlist (in seconds)" << endl;
      cout << "o - Output full playlist" << endl;
      cout << "q - Quit" << endl << endl;
      while (menuOp != 'a' && menuOp != 'd' && menuOp != 'c' &&
             menuOp != 's' && menuOp != 't' && menuOp != 'o' && menuOp != 'q') 
      {
         cout << "Choose an option:";
         cin >> menuOp;
         cout << endl;
         //maybe add endl
      }

      //add
      if(menuOp == 'a')
      {
         cout << "ADD SONG" << endl
         << "Enter song's unique ID:";
         cin >> uniqueID;
         cout << endl;
         cout << "Enter song's name:";
         cin.ignore();
         getline(cin, songName);
         cout << endl;
         cout << "Enter artist's name:";
         getline(cin, artistName);
         cout << endl;
         cout << "Enter song's length (in seconds):";
         cin >> songLength;
         cout << endl << endl; // added endline

         PlaylistNode* newSong = new PlaylistNode(uniqueID, songName, artistName, songLength);
         if(headNode == nullptr)
         {
            headNode = newSong;
            tailNode = newSong;
         }
         else
         {
            tailNode->InsertAfter(newSong);
            tailNode = newSong;
         }

         numNodes++;
         totalTime += newSong->GetSongLength();
      }

      //delete
      if(menuOp == 'd')
      {
         cout << "REMOVE SONG" << endl 
         << "Enter song's unique ID:";
         cin >> uniqueID;
         cout << endl;

         //popfront
         if(headNode->GetID() == uniqueID)
         {
            cout << "\"" << headNode->GetSongName() << "\" removed." << endl << endl;
            if(headNode == tailNode)
            {
               delete headNode;
               headNode = nullptr;
               tailNode = nullptr;
               totalTime = 0;
            }
            else
            {
               totalTime -= headNode->GetSongLength();
               prevNode = headNode;
               headNode = headNode->GetNext();
               delete prevNode;
               prevNode = nullptr;
            }
         }

         //Middle/Tail
         else
         {
            prevNode = headNode;
            // for(; prevNode != nullptr; prevNode = prevNode->GetNext())
            while(prevNode != nullptr)
            {
               if(prevNode->GetNext()->GetID() == uniqueID)
               {
                  currNode = prevNode->GetNext();
                  prevNode->SetNext(currNode->GetNext());

                  if(currNode->GetNext() == nullptr)
                  {
                     tailNode = prevNode;
                  }

                  cout << "\"" << currNode->GetSongName() << "\" removed." << endl << endl;
                  totalTime -= currNode->GetSongLength();
                  delete currNode;
                  prevNode = nullptr;
               }
               else
               {
                  prevNode = prevNode->GetNext();
               }
               
            }
         }
         
         numNodes--; 
      }

      if(menuOp == 'c')
      {
         cout << "CHANGE POSITION OF SONG" << endl 
         << "Enter song's current position:";
         cin >> songPosition;
         cout << endl;
         cout << "Enter new position for song:";
         cin >> newPosition;
         cout << endl;

         if(newPosition > numNodes)
         {
            newPosition = numNodes;
         }
         else if(newPosition < 1)
         {
            newPosition = 1;
         }

         if(songPosition == 1)
         {
            currNode = headNode;
            headNode = headNode->GetNext();
         }
         else
         {
            int n = 1;
            prevNode = headNode;
            
            //remove from list
            while(n != songPosition)
            {
               if(songPosition == (n+1))
               {
                  currNode = prevNode->GetNext();
                  prevNode->SetNext(currNode->GetNext());

                  if(currNode->GetNext() == nullptr)
                  {
                     tailNode = prevNode;
                  }
                  n = songPosition;
               }
               else
               {
                  prevNode = prevNode->GetNext();
                  n++;
               }
            }
         }

         currNode->SetNext(songNode); //set to nullptr


         //insert
         int n = 1;
         insertPosNode = headNode;
         if(newPosition == 1)
         {
            currNode->SetNext(insertPosNode);
            headNode = currNode;

         }
         else
         {
            while(n != newPosition)
            {
               if(newPosition == (n + 1))
               {
                  insertPosNode->InsertAfter(currNode);
                  n = newPosition;
               }
               else
               {
                  insertPosNode = insertPosNode->GetNext();
                  n++;
               }
            }
         }
         cout << "\"" << currNode->GetSongName() << "\" moved to position " << newPosition << endl << endl; 
      }
      //output
      if(menuOp == 's')
      {
         cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl
         << "Enter artist's name:";
         cin.ignore();
         getline(cin, artistName);
         cout << endl << endl;

         currNode = headNode;
         int counter = 1;
         for(; currNode != nullptr; currNode = currNode->GetNext())
         {
            if(currNode->GetArtistName() == artistName)
            {
               cout << counter << "." << endl;
               currNode->PrintPlaylistNode();
               cout << endl;
            }
            counter++;
         }
      }

      if(menuOp == 't')
      {
         cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl
         << "Total time: " << totalTime << " seconds" << endl << endl;
      }

      if(menuOp == 'o')
      {
         int counter = 1;
         currPrintNode = headNode;

         cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
         if(currPrintNode == nullptr)
         {
            cout << "Playlist is empty" << endl << endl; //added endl
         }

         while(currPrintNode != nullptr)
         {
            cout << counter << "." << endl;
            currPrintNode->PrintPlaylistNode();
            cout << endl; // extra endl
            currPrintNode = currPrintNode->GetNext();
            counter ++;
         }
      }


      //quit
   }
    
}