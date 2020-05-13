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


    StreamList& list = *((MusicManager*)DS)->GetListOfStreams();
    StreamListNode* zero_streams_node = GetListFirstNode();

    // all songs now point to the zero streams node
    for(int i = 0; i < artist_to_add.GetTotalNumOfSongs(); i++){
        artist_to_add.SetStreamsNumForSong(i, zero_streams_node);
    }

    AvlTree<AvlTree<int,int>,int>& streams_tree = artist_to_add.GetNumOfStreamsTree();
    AvlTree<int,int>& songs_tree = AvlTree<int,int>();
    //USE AVITAL's FUNCTION TO INSERT ALL SONGS AS NODES TO streams_tree - as "0"
        // .insert(streams_tree,0);

    tree.insert(artist_to_add, artistID);

    AvlTree<(AvlTree<int,int>)*,int>& node_tree = zero_streams_node->getNodeAvlTree();
    node_tree.insert((&(*(tree.getElementptr(artistID))->GetNumOfStreamsTree())),artistID);


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
        if(i != 0){
            if(node_tree.getFirst == nullptr){
                *((MusicManager*)DS)->GetListOfStreams().removeNode(&num_node);
            }
        }
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
        // delete the node if there are no more artists left

}





StatusType AddToSongCount(void* DS, int artistID, int songID){
    // Check ERRORS

    //get the tree, the artist and the list
    AvlTree<Artist,int>& tree = *((MusicManager*)DS)->GetArtistsTree();
    Artist& artist = *(tree.getElementptr(artistID));
    StreamList& list_of_streams = *((MusicManager*)DS)->GetListOfStreams();
    AvlTree<int,int>* node_to_point_to = nullptr;
    StreamListNode* stream_list_node_to_point_to = nullptr;

    //change in the ArtistsTree
    AvlTree<AvlTree<int,int>,int>& num_of_streams_tree = artist.GetNumOfStreamsTree();
    StreamListNode* num_of_streams_list_node = artist.GetSongNumOfStreamsNode(songID);
    int songs_num_of_streams = *(num_of_streams_list_node)->GetNodeNumOfStreams();
    // remove song node
    AvlTree<int,int>& num_of_streams_tree_node = *(num_of_streams_tree.getElementptr(songs_num_of_streams));
    num_of_streams_tree_node.remove(songID);
    if(num_of_streams_tree_node.getFirst() == nullptr){
        num_of_streams_tree.remove(songs_num_of_streams);
    }
    // insert song to the next num_of_streams node
    if(num_of_streams_tree.findKeyAlreadyExists(songs_num_of_streams+1)){
        *(num_of_streams_tree.getElementptr(songs_num_of_streams+1))->insert(songID,songID);
    }
    else if{
        AvlTree<int,int>& new_songs_tree = AvlTree<int,int>();
        new_songs_tree.insert(songID,songID);
        num_of_streams_tree.insert(new_songs_tree,songs_num_of_streams+1);
        node_to_point_to = num_of_streams_tree.getElementptr(songs_num_of_streams+1);
    }

    /* OLD CODE
    AvlTree<int,int>& num_of_streams_tree_next_node = *(num_of_streams_tree.getNext()) // HOW TO USE GetNext?
    if(num_of_streams_tree_next_node.getKey() == ) {         // HOW TO USE GetKey?
        // get the next num_of_streams node
        // check if +1 exists
        // if yes - add the song to it
        node_to_point_to = &num_of_streams_tree_next_node;
    }
    else if{
        AvlTree<int,int>& new_songs_tree = AvlTree<int,int>();
        new_songs_tree.insert(songID,songID);
        num_of_streams_tree.insert(new_songs_tree, songs_num_of_streams+1);
        node_to_point_to = num_of_streams_tree.getElementptr(songs_num_of_streams+1);
    }

     */







    // change in the List
    StreamListNode* num_of_streams_list_next_node = num_of_streams_list_node->getNextNode();
    if(*(num_of_streams_list_next_node)->GetNodeNumOfStreams() == songs_num_of_streams+1){
        AvlTree<(AvlTree<int,int>)*,int>& num_of_streams_list_next_node_tree =
                *(num_of_streams_list_next_node)->getNodeAvlTree();
        num_of_streams_list_next_node_tree.insert(node_to_point_to,artistID);
        stream_list_node_to_point_to = num_of_streams_list_next_node;
    }
    else if{
        AvlTree<(AvlTree<int,int>)*,int>& new_node_tree = AvlTree<(AvlTree<int,int>)*,int>();
        new_node_tree.insert(node_to_point_to,artistID);
        list_of_streams.insertNode(num_of_streams_list_node,new_node_tree,songs_num_of_streams+1);
        stream_list_node_to_point_to = num_of_streams_list_node->getNextNode();
    }
    // remove the artist's node from the original node's tree
    AvlTree<(AvlTree<int,int>)*,int>& num_of_streams_list_node_tree = *(num_of_streams_list_node)->getNodeAvlTree();
    num_of_streams_list_node_tree.remove(artistID);
    if(*(num_of_streams_list_node)->GetNodeNumOfStreams() != 0){
        if(num_of_streams_list_node_tree.getFirst() == nullptr){
            list_of_streams.removeNode(num_of_streams_list_node);
        }
    }

    // change in the songs array
    artist.SetStreamsNumForSong(songID,stream_list_node_to_point_to);




    //get the tree, the artist and the list

    //change in the ArtistsTree
        // find the songs num_of_streams in the array
        // get the right num_of_streams tree
        // remove song node from it
            // check if it was the only song in the tree
                // if yes - remove the num_of_streams node
        // get the next num_of_streams node
            // check if +1 exists
                // if yes - add the song to it
                // if no - create a new num_of_streams node and add the song to it

    // change in the List
        // get the node in the StreamList from the songs array
        // get the node's AVLTree
        // check if next exists
            // if yes - get the pointer to the element (the tree)
            // if no - create one and add
// OLD PART
            // get the next StreamListNode
                // check if +1
                    // if yes - add the artist to it - pointer to the new "num_of_streams" node
                    // if no
                        // add a new +1 node to the StreamList
                        // add the artist to the node's tree - pointer the the new "num_of_streams" node
// END OF OLD PART
        // remove the artist's node from the tree
            // check if it wasn't the first node
                // check if it was the only song in the tree
                    // if yes - remove the node from the List

    // change in the songs array
        // change the pointer in the songID index to points to the new node in the StreamList

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
        current_Node_of_hearings=current_Node_of_hearings->getNextNode();
    }

}




// check if that is the way to use DELETE
void Quit(void** DS){
    //delete for all init "new"s?
    // put NULL in the pointer
}


#endif //WET1_STRUCTS_MUSICMANAGER_H
