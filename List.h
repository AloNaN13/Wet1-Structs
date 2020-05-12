//
// Created by User on 5/8/2020.
//

#ifndef WET1_STRUCTS_LIST_H
#define WET1_STRUCTS_LIST_H


#include "AvlTree.h"
#include "Artist.h"

typedef enum StreamListResult_t{
    SUCCESS,
    ALLOCATION_ERROR,
    NODE_ALREADY_EXISTS,
    NODE_DOESNT_EXISTS
}StreamListResult;



class StreamListNode{
private:
    const int num_of_streams;
    AvlTree<(AvlTree<int,int>)*,int>& stream_artists;
    StreamListNode* prev_node;
    StreamListNode* next_node;
public:
    StreamListNode(AvlTree<(AvlTree<int,int>)*,int>& stream_artists, int num_of_streams):
            stream_artists(stream_artists), num_of_streams(num_of_streams), prev_node(nullptr),
            next_node(nullptr) {};
    ~StreamListNode() = default;
    //StreamListNode(const StreamListNode& node) = delete;
    //StreamListNode& operator=(const StreamListNode& node) = delete;

    int GetNodeNumOfStreams() {return this->num_of_streams;};
    StreamListNode* getPrevNode() { return this.prev_node;};
    void SetPrevNode(StreamListNode* new_prev) { this->prev_node=new_prev;}; // void?
    StreamListNode* getNextNode() { return this.next_node;};
    void SetNextNode(StreamListNode* new_next) { this->next_node=new_next;}; // void?
    AvlTree<(AvlTree<int,int>)*,int>& getNodeAvlTree() {return this.stream_artists;};
    //ListNode& getNodeFromKey(const Key key);

};



class StreamList{
private:
    // need to get put of the private
    // put the StreamListNode back?

    StreamListNode* first_node;
    StreamListNode* last_node;
    //iterator?

    // Key& // not sure if needed
    //bool FindKeyAlreadyExists(const Key& key);


public:
    StreamList(): first_node(nullptr), last_node(nullptr) {};
    ~StreamList();
    //StreamList(const StreamList& list) = delete;
    //StreamList& operator=(const StreamList& list) = delete;

    AvlTree<(AvlTree<int,int>)*,int>& getAvlTreeFromNode(StreamListNode& node) {return node.getNodeAvlTree();};

    StreamListNode* GetListFirstNode() {return this->first_node;};
    StreamListNode* GetListLastNode() {return this->last_node;};

    StreamListNode* getNodePrev(StreamListNode* node) { return *node->getPrevNode();};
    StreamListNode* getNodeNext(StreamListNode* node) { return *node->getNextNode();};


    ListResult insertNode(StreamListNode* curr_node, AvlTree<(AvlTree<int,int>)*,int>& stream_artists, int& num_of_streams);
    ListResult removeNode(StreamListNode* node);

};



StreamList::~StreamList(){
    // to implement
}


// inserts after the curr_node
ListResult StreamList::insertNode(StreamListNode* curr_node, AvlTree<(AvlTree<int,int>)*,int>& stream_artists, int& num_of_streams) {

    // check if num_of_streams exists?
    /*
        if(FindKeyAlreadyExists(key)){
        return NODE_ALREADY_EXISTS;
     */

    StreamListNode* new_node = new StreamListNode(stream_artists,num_of_streams); // why new?

    // check if the list is empty? probably not, cuz ill make sure there's at least 1 node (0 streams)

    //check the following pointers use

    if(curr_node->next_node != nullptr){
        *new_node->next_node = curr_node->next_node;
        *curr_node->next_node->prev_node = new_node;
    }
    *new_node->prev_node = curr_node;
    *curr_node->next_node = new_node;

    return SUCCESS;

}


ListResult StreamList::removeNode(StreamListNode* node) {

    /*
    if(!FindKeyAlreadyExists(key)){
    return  NODE_DOESNT_EXISTS;
    }
     */

    //check the following pointers use

    *node->prev_node->next_node = *node->next_node;
    *node->next_node->prev_node = *node->prev_node;

    delete(node);
    return SUCCESS;

}

























/*


typedef struct list* List;

typedef void* Element;

typedef Element (*ElemCopyFunction)(Element);
typedef void (*ElemFreeFunction)(Element);

// Function that returns true if a==b, or false otherwise.
typedef bool (*ElemEqualFunction)(Element a, Element b);

// Function that returns positive if a>b, negative if a<b, or zero if a==b.
typedef int (*ElemCompareFunction)(Element a, Element b);

// Function for checking a condition on an element.
typedef bool (*ElemConditionFunction)(Element, void* param);



typedef enum {
    LIST_SUCCESS,
    LIST_OUT_OF_MEMORY,
    LIST_NULL_ARG,
    LIST_INVALID_CURRENT
} ListResult;

List listCreate(ElemCopyFunction, ElemFreeFunction);
List listCopy(List list);
void listDestroy(List list);

Element listGetFirst(List list);   // returns NULL if list is empty
Element listGetNext(List list);    // returns NULL if no more elements
Element listGetCurrent(List list);

ListResult listInsertFirst(List list, Element element);
ListResult listInsertLast(List list, Element element);
ListResult listInsertBeforeCurrent(List list, Element element);
ListResult listInsertAfterCurrent(List list, Element element);
ListResult listRemoveCurrent(List list);

void listClear(List list);
int listGetSize(List list);
bool listIsEmpty(List list);

ListResult listSort(List list, ElemCompareFunction compare);
List listFilter(List list, ElemConditionFunction condition, void* param);

// Macro to enable simple iteration
#define LIST_FOREACH(Type, element, list) \
  for (Type element = listGetFirst(list); \
     element != NULL; \
     element = listGetNext(list))



*/





#endif //WET1_STRUCTS_LIST_H
