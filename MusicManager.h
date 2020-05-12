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

    // all songs now point to the zero streams node
    for(int i = 0; i < artist_to_add.GetTotalNumOfSongs(); i++){
        artist_to_add.SetStreamsNumForSong(i, zero_streams_node);
    }



    

    tree.insert(artist_to_add, artistID);

    StreamList& list = *((MusicManager*)DS)->GetListOfStreams();
    StreamListNode* zero_streams_node = GetListFirstNode();


    AvlTree<(AvlTree<int,int>)*,int>& node_tree = zero_streams_node->getNodeAvlTree();
    node_tree.insert(/*THE POINTER TO THE STREAM_NUM*/,artistID);


    // insert one node of "0" to the AvlTree of the artist - for NumOfStreams
    // create AvlTree for all the songs
        // insert it to the "0" node of NumOfSons
        // insert nodes to it for all songIDs - USE AVITAL'S FUNCTION

    return SUCCESS;

}





StatusType RemoveArtist(void* DS, int artistID){
    // Check ERRORS

    AvlTree<Artist,int>& tree = *((MusicManager*)DS)->GetArtistsTree();
    Artist& artist = *(tree.getElementptr(artistID));

    // COMPLEXITY GOOD ENOUGH? NO NEED TO MAKE NULLS?
    for(int i = 0; i < artist.GetTotalNumOfSongs(); i++){
        StreamListNode* num_node = artist.GetSongNumOfStreamsNode(i);
        AvlTree<(AvlTree<int,int>)*,int>& node_tree = num_node->getNodeAvlTree();
        node_tree.remove(artistID);
        artist.SetStreamsNumForSong(i,nullptr);
    }
    tree.remove(artistID);

    // DELETE THE TREE IF NO MORE ARTISTS!





    // go to songs list
        // for every song
            // go to the node in the StreamList
            // if NULL - proceed to next song
            // remove the artist pointer from each node
                // remove the artist by key in the node's AVL Tree
            // change the pointer to NULL
        // delete the artist - remove from tree
        // delete the node if there are no more artists left

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
    AvlTree<int,int>* songs_of_current_artist_with_num_streams;
    int* song;
    int current_ArtistId;
    while (count<numOfSongs){
        int numStreams=0;
        songs_of_current_artist_with_num_streams=(current_Node_of_hearings->getNodeAvlTree()).getFirst();

        while (count<numOfSongs &&songs_of_current_artist_with_num_streams){
            song=songs_of_current_artist_with_num_streams->getFirst();
            current_ArtistId=(current_Node_of_hearings->getNodeAvlTree()).getKey();
            while (song &&count<numOfSongs){
                artists[count]=current_ArtistId;
                songs[count]=(current_Node_of_hearings->getNodeAvlTree()).getKey();

                count++;
                song=songs_of_current_artist_with_num_streams->getNext();
            }

            songs_of_current_artist_with_num_streams=(current_Node_of_hearings->getNodeAvlTree()).getNext();
        }

    }

}





void Quit(void** DS){
    //write
}


#endif //WET1_STRUCTS_MUSICMANAGER_H
