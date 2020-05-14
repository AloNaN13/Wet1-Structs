//
// Created by User on 5/13/2020.
//

#include "library1.h"
#include "MusicManager.h"



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
void* Init(){

    MusicManager* DS=new MusicManager();
    return (void*)DS;
}

StatusType AddArtist(void* DS, int artistID, int numOfSongs){
    if(DS== nullptr){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMAddArtist(artistID,numOfSongs));



}


StatusType RemoveArtist(void* DS, int artistID) {
    if(DS== nullptr){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMRemoveArtist(artistID));


}

StatusType AddToSongCount(void* DS, int artistID, int songID){
    if(DS== nullptr){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMAddToSongCount(artistID,songID));


}


StatusType NumberOfStreams(void* DS, int artistID, int songID, int* streams){
    if(DS== nullptr){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMNumberOfStreams(artistID,songID,streams));


}


StatusType GetRecommendedSongs(void* DS, int numOfSongs, int* artists, int* songs){
    if(DS== nullptr||numOfSongs<=0){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMgetRecommendedSongs(numOfSongs,artists,songs));
}

void Quit(void**DS ){
    delete ((MusicManager*)(*DS));
    *DS= nullptr;
}

