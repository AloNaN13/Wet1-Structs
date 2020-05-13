//
// Created by User on 5/13/2020.
//
#include "library1.h"
#include "MusicManager.h"

void* Init(){

    MusicManager* DS=new MusicManager();
    return (void*)DS;
}

StatusType AddArtist(void* DS, int artistID, int numOfSongs){


}


StatusType RemoveArtist(void* DS, int artistID) {

}

StatusType AddToSongCount(void* DS, int artistID, int songID){

}


StatusType NumberOfStreams(void* DS, int artistID, int songID, int* streams){

}


StatusType GetRecommendedSongs(void* DS, int numOfSongs, int* artists, int* songs){
    
}