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
    if(DS== nullptr){
        return
    }


}


StatusType RemoveArtist(void* DS, int artistID) {

}

StatusType AddToSongCount(void* DS, int artistID, int songID){

}


StatusType NumberOfStreams(void* DS, int artistID, int songID, int* streams){

}


StatusType GetRecommendedSongs(void* DS, int numOfSongs, int* artists, int* songs){
    
}

StatusType quit(void**DS ){

}

StatusType changeMMResultToStatusType(MMStatusType result){
    if(result==MM_SUCCESS){
        return SUCCESS;
    }
    if(result==MM_FAILURE){
        return FAILURE;
    }
    if(result==MM_ALLOCATION_ERROR){
        return  ALLOCATION_ERROR;
    }
    if(result=MM_INVALID_INPUT){
        return  INVALID_INPUT;
    }
}