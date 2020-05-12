//
// Created by User on 5/10/2020.
//

#ifndef WET1_STRUCTS_MUSICMANAGER_H
#define WET1_STRUCTS_MUSICMANAGER_H

#include "AvlTree.h"
#include "List.h"
#include "Artist.h"

// should these enums be exceptions?
typedef enum StatusType_t{
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
    StatusType getRecommendedSongs( int numOfSongs, int* artists, int* songs);

};





void * Init(){

    // create AVLTree of Artist
    // create StreamList with Node 0

    return DS;
}



StatusType AddArtist(void* DS, int artistID, int numOfSongs){
    // check ERRORS

    AvlTree<Artist,int>& tree = *((MusicManager*)DS)->GetArtistsTree();
    Artist& artist_to_add = Artist(numOfSongs);
    tree.insert(artist_to_add, artistID);

    StreamList& list = *((MusicManager*)DS)->GetListOfStreams();
    StreamListNode* zero_streams_node = GetListFirstNode();

    // all songs now point to the zero streams node
    for(int i = 0; i < artist_to_add.GetTotalNumOfSongs(); i++){
        artist_to_add.SetStreamsNumForSong(i, zero_streams_node);
    }

    return SUCCESS;

}





StatusType RemoveArtist(void* DS, int artistID){
    AvlTree<Artist,int>& tree = *((MusicManager*)DS)->GetArtistsTree();
    Artist& artist= *(tree.getElementptr(artistID));

    Artist()

}





StatusType AddToSongCount(void* DS, int artistID, int songID){
    //write
}





StatusType NumberOfStreams(void* DS, int artistID, int songID, int* streams){
    // return ERRORS

    AvlTree<Artist,int>& tree = *((MusicManager*)DS)->GetArtistsTree();
    Artist& artist= *(tree.getElementptr(artistID));
    int num = artist.GetSongNumOfStreams(songID);

    *streams = num;

    return SUCCESS;

}





StatusType GetRecommendedSongs(void* DS, int numOfSongs, int* artists, int* songs){
    if(DS== nullptr || numOfSongs<=0){
        return INVALID_INPUT;
    }
    DS.getRecommendedSongs( int numOfSongs, int* artists, int* songs);

}







void Quit(void** DS){
    //write
}


#endif //WET1_STRUCTS_MUSICMANAGER_H
