//
// Created by User on 5/10/2020.
//

#ifndef WET1_STRUCTS_MUSICMANAGER_H
#define WET1_STRUCTS_MUSICMANAGER_H

#include "AvlTree.h"
#include "List.h"
#include "Artist.h"

// should these enums be exceptions?
typedef StatusType_t{
    ALLOCATION_ERROR,
    INVALID_INPUT,
    FAILURE,
    SUCCESS
}StatusType;


// MusicManager Class?
class MusicManager{
private:
    AvlTree<Artist,int> artists_tree;
    StreamList list_of_streams;
public:
    MusicManager(AvlTree<Artist,int>& artists_tree, StreamList& list_of_streams):
        artists_tree(artists_tree), list_of_streams(list_of_streams);
    ~MusicManager() = default;
    MusicManager(const MusicManager& music_manager) = default;
    MusicManager& operator=(const MusicManager& music_manager) = default;

    //methods
    StreamList& GetListOfStreams() {return this->list_of_streams;};
    AvlTree<Artist,int>& GetArtistsTree() {return this->artists_tree;};

};





void * Init(){

    // create AVLTree of Artist
    // create StreamList with Node 0

    return DS;
}



StatusType AddArtist(void* DS, int artistID, int numOfSongs){
    //write
}





StatusType RemoveArtist(void* DS, int artistID){
    //write
}





StatusType AddToSongCount(void* DS, int artistID, int songID){
    //write
}





StatusType NumberOfStreams(void* DS, int artistID, int songID, int* streams){
    // return ERRORS

    AvlTree<Artist,int>& tree = *((MusicManager*)DS)->GetArtistsTree();
    Artist& artist= tree.getElementptr(artistID);
    int num = artist.GetSongNumOfStreams(songID);

    *streams = num;

    return SUCCESS;

}





StatusType GetRecommendedSongs(void* DS, int numOfSongs, int* artists, int* songs){
    //write
}







void Quit(void** DS){
    //write
}


#endif //WET1_STRUCTS_MUSICMANAGER_H
