//
// Created by User on 5/10/2020.
//

#ifndef WET1_STRUCTS_MUSICMANAGER_H
#define WET1_STRUCTS_MUSICMANAGER_H


// should these enums be exceptions?
typedef StatusType_t{
    ALLOCATION_ERROR,
    INVALID_INPUT,
    FAILURE,
    SUCCESS
}StatusType;

// DS Class?

void * Init(){

    return DS;
}



StatusType AddArtist( void * DS, int artistID, int numOfSongs){
    //write
}





StatusType RemoveArtist( void * DS, int artistID){
    //write
}





StatusType AddToSongCount( void * DS, int artistID, int songID){
    //write
}





StatusType NumberOfStreams( void * DS, int artistID, int songID, int * streams){
    //write
}





StatusType GetRecommendedSongs( void * DS, int numOfSongs, int * artists, int * songs){
    //write
}







void Quit( void ** DS){
    //write
}


#endif //WET1_STRUCTS_MUSICMANAGER_H
