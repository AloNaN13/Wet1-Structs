//
// Created by User on 5/8/2020.
//

#ifndef WET1_STRUCTS_ARTIST_H
#define WET1_STRUCTS_ARTIST_H

#include "AvlTree.h"
//#include "List.h"

class Artist{
private:
    //int artist_id; - probably no need
    int total_num_of_songs;
    StreamListNode** full_songs_list;
    AvlTree& num_of_streams_tree;
public:
    Artist(/*int id*/ int num_of_songs);
    ~Artist();
    Artist(const Artist& a) = default;
    Artist& operator=(const Artist& a) = default;

    getters-
    int GetArtistID();// Needed?
    int GetNumOfStreams

    editors
    /ERRORS ChangeStreamsNumForSong(int song_id);

};

Artist::Artist(int num_of_songs) {
    //artist_id = id;

    // allocate space for full_song_list
    total_num_of_songs = num_of_songs;
    full_songs_list = new StreamListNode*[num_of_songs];

    // link all songs the the Node 0 in StreamList - to implement in the AddArtist Func?

    // create AvlTree for streams_tree
    num_of_streams_tree = AvlTree<AvlTree<int><int>><int>();

    //return this?
}

Artist::~Artist() {

    // delete full_song_list
    delete[] full_songs_list;

    // delete nodes in AvlTree for streams_tree - use the destructor?

    // cut ties to streams_list - to implement in the RemoveArtist Func?

}


class Song{
private:
    int song_id;
    /*int**/ num_of_times_streamed; // should point to the list?
public:
    Song();
    ~Song();
    Song(const Song& s) = delete;
    Song& operator=(const Song& s) = delete;

    editors:
            change num_of_times_streamed
};

Song::Song() {
    song_id = ;
    // pointer should point to 0 in the linked list
}

Song::~Song() {

}



// what about the list of streams? should I write a new linked list?


#endif //WET1_STRUCTS_ARTIST_H
