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
    int totalNumOfSongs;
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

    return new MusicManager;
}



StatusType AddArtist(void* DS, int artistID, int numOfSongs){
    // check ERRORS

    AvlTree<Artist,int>& tree = *((MusicManager*)DS)->GetArtistsTree();
    Artist& artist_to_add = Artist(artistID, numOfSongs);
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
    // Check ERRORS

    AvlTree<Artist,int>& tree = *((MusicManager*)DS)->GetArtistsTree();
    Artist& artist = *(tree.getElementptr(artistID));

    // COMPLEXITY GOOD ENOUGH? NO NEED TO MAKE NULLS?
    for(int i = 0; i < artist.GetTotalNumOfSongs(); i++){
        StreamListNode* num_node = artist.GetSongNumOfStreamsNode(i);
        AvlTree<Artist*,int>& node_tree = num_node->getNodeAvlTree();
        node_tree.remove(artistID);
        artist.SetStreamsNumForSong(i,nullptr);
    }
    tree.remove(artistID);

    // go to songs list
        // for every song
            // go to the node in the StreamList
            // if NULL - proceed to next song
            // remove the artist pointer from each node
                // remove the artist by key in the node's AVL Tree
            // change the pointer to NULL
        // delete the artist - remove from tree

}





StatusType AddToSongCount(void* DS, int artistID, int songID){
    // Check ERRORS

    //get the tree, the artist and the list
    AvlTree<Artist,int>& tree = *((MusicManager*)DS)->GetArtistsTree();
    Artist& artist = *(tree.getElementptr(artistID));
    StreamList& list_of_streams = *((MusicManager*)DS)->GetListOfStreams();

    // get the node in list and its num_of_streams
    StreamListNode* curr_num_node = artist.GetSongNumOfStreamsNode(songID);
    AvlTree<Artist*,int> curr_num_node_tree = curr_num_node->getNodeAvlTree();
    int num = curr_num_node->GetNodeNumOfStreams();

    list_of_streams.insertNode(curr_num_node, curr_num_node_tree, num+1);

    curr_num_node->SetPrevNode();

}





StatusType NumberOfStreams(void* DS, int artistID, int songID, int* streams){
    // return ERRORS

    AvlTree<Artist,int>& tree = *((MusicManager*)DS)->GetArtistsTree();
    Artist& artist= *(tree.getElementptr(artistID));
    StreamListNode* num_node = artist.GetSongNumOfStreams(songID);

    int num = num_node->GetNodeNumOfStreams();
    *streams = num;

    return SUCCESS;

}





StatusType GetRecommendedSongs(void* DS, int numOfSongs, int* artists, int* songs){
    if(DS== nullptr || numOfSongs<=0){
        return INVALID_INPUT;
    }
    DS.getRecommendedSongs( int numOfSongs, int* artists, int* songs);
}

StatusType MusicManager:: getRecommendedSongs( int numOfSongs, int* artists, int* songs){
    if(numOfSongs>totalNumOfSongs){
        return FAILURE;
    }
    StreamListNode* current_Node_of_hearings=list_of_streams.GetListLastNode();
    int count=0;;
    Artist* currentArtist;
    AvlTree<int,int> songs_at_num_streams;
    int* song;
    while (count<numOfSongs){//need to get the artist
        int numStreams=0;
        AvlTree<Artist*,int> currentNumHearings=current_Node_of_hearings->getNodeAvlTree();
        currentArtist=*(currentNumHearings.getFirst());
        while (count<numOfSongs&& currentArtist!=nullptr){
            songs_at_num_streams=currentArtist->getSongsWithNumOfStreams();
            song=songs_at_num_streams.getFirst();
            //artistID
            while (song!= nullptr &&count<numOfSongs){

            }
            currentArtist=*(currentNumHearings.getNext());
        }

    }

}





void Quit(void** DS){
    //write
}


#endif //WET1_STRUCTS_MUSICMANAGER_H
