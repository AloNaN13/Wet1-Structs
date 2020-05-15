//
// Created by User on 5/8/2020.
//

#include "List.h"



void StreamList::deleteAllStreamNodes(StreamListNode* node) {
    if(node){
        deleteAllStreamNodes((node->getNextNode()));
        delete(node);
    }
}

StreamList::~StreamList(){
    if(first_node){
        deleteAllStreamNodes(first_node);
    }
}


// inserts after the curr_node
StreamListResult StreamList::insertNode(StreamListNode* curr_node, AvlTree<AvlTree<int,int>*,int>& stream_artists, int num_of_streams) {

    // check if num_of_streams exists?
    /*
        if(FindKeyAlreadyExists(key)){
        return NODE_ALREADY_EXISTS;
     */

    StreamListNode* new_node = new StreamListNode(stream_artists,num_of_streams); // why new?

    // check if the list is empty? probably not, cuz ill make sure there's at least 1 node (0 streams)

    //check the following pointers use

    if(curr_node->getNextNode() != nullptr){
        new_node->SetNextNode(curr_node->getNextNode());
        curr_node->getNextNode()->SetPrevNode(new_node);
    }
    new_node->SetPrevNode(curr_node);
    curr_node->SetNextNode(new_node);

    if(curr_node == last_node){
        last_node = curr_node->getNextNode();
    }

    return SL_SUCCESS;

}


StreamListResult StreamList::removeNode(StreamListNode* node) {

    /*
    if(!FindKeyAlreadyExists(key)){
    return  NODE_DOESNT_EXISTS;
     */

    //check the following pointers use

    if(node == last_node){
        last_node = node->getPrevNode();
    }
    node->getPrevNode()->SetNextNode(node->getNextNode());
    node->getNextNode()->SetPrevNode(node->getPrevNode());

    delete(node);
    return SL_SUCCESS;

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


