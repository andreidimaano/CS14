#include "Playlist.h"
#include <iostream>

using namespace std;

PlaylistNode::PlaylistNode()
{
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}
PlaylistNode::PlaylistNode(const string & ID, const string & name, const string & artist, const int & len)
{
    uniqueID = ID;
    songName = name;
    artistName = artist;
    songLength = len;
    nextNodePtr = nullptr;
}
void PlaylistNode::InsertAfter(PlaylistNode* p)
{
    if(this->nextNodePtr == nullptr)
    {
        this->nextNodePtr = p;
    }
    else
    {
        PlaylistNode* temp = this->nextNodePtr;
        this->nextNodePtr = p;
        p->nextNodePtr = temp;
    }
}
void PlaylistNode::SetNext(PlaylistNode* nodePtr)
{
    this->nextNodePtr = nodePtr;   
}
string PlaylistNode::GetID() const
{
    return uniqueID;
}
string PlaylistNode::GetSongName() const
{
    return songName;
}
string PlaylistNode::GetArtistName() const
{
    return artistName;
}
int PlaylistNode::GetSongLength() const
{
    return songLength;
}
PlaylistNode* PlaylistNode::GetNext() const
{
    return nextNodePtr;
}
void PlaylistNode::PrintPlaylistNode() const
{
    cout << "Unique ID: " << this->GetID() << endl
    << "Song Name: " << this->GetSongName() << endl
    << "Artist Name: " << this->GetArtistName() << endl
    << "Song Length (in seconds): " << this->GetSongLength() << endl;
}