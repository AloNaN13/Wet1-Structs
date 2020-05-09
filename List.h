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




class StreamList{
private:
    class StreamListNode{
    public:
        int num_of_streams;
        AvlTree<Artist*,int> stream_artists;
        StreamListNode* prev_node;
        StreamListNode* next_node;

        StreamListNode(AvlTree<Artist*,int>& stream_artists, int num_of_streams):
            stream_artists(stream_artists), num_of_streams(num_of_streams), prev_node(nullptr),
            next_node(nullptr){};
        ~StreamListNode() = default;
        StreamListNode(const StreamListNode& node) = delete;
        StreamListNode& operator=(const StreamListNode& node) = delete;

        StreamListNode* getPrevNode() { return this.prev_node;};
        void SetPrevNode(StreamListNode* new_prev) { this->prev_node=new_prev;}; // void?
        StreamListNode* getNextNode() { return this.next_node;};
        void SetNextNode(StreamListNode* new_next) { this->next_node=new_next;}; // void?
        AvlTree<Artist*,int>& getNodeAvlTree() {return this.stream_artists;};
        //ListNode& getNodeFromKey(const Key key);

    };

    StreamListNode* first_node;
    StreamListNode* last_node;
    //iterator?

    // Key& // not sure if needed
    //bool FindKeyAlreadyExists(const Key& key);



public:
    StreamList(): first_node(nullptr), last_node(nullptr);
    ~StreamList();
    StreamList(const StreamList& list) = delete;
    StreamList& operator=(const StreamList& list) = delete;

    AvlTree<Artist*,int>& getAvlTreeFromNode(StreamListNode& node) {return node.getNodeAvlTree();};

};



StreamList::~StreamList(){
    //write
}



































































template <class Element,class Key>
class List{
private:
    class ListNode{
    public:
        Key& key;
        Element& data;
        ListNode* prev_node;
        ListNode* next_node;

        ListNode(Key& key, Element& data): key(key), data(data), prev_node(nullptr),
                next_node(nullptr){};
        ~ListNode() = default;
        ListNode(const ListNode& node) = delete;
        ListNode& operator=(const ListNode& node) = delete;

        ListNode* getPrevNode() { return this.prev_node;};
        void SetPrevNode(ListNode* new_prev) { this->prev_node=new_prev;}; // void?
        ListNode* getNextNode() { return this.next_node;};
        void SetNextNode(ListNode* new_next) { this->next_node=new_next;}; // void?
        Element& getNodeData() {return this.data;};
        //ListNode& getNodeFromKey(const Key key);

    };

    ListNode* first_node;
    ListNode* last_node;
    //iterator?

    // Key& // not sure if needed
    //bool FindKeyAlreadyExists(const Key& key);



public:
    List(): first_node(nullptr), last_node(nullptr);
    ~List();
    List(const List& node) = delete;
    List& operator=(const List& node) = delete;


    Element& getDataFromNode(ListNode& node) {return node.getNodeData();};

};



List<Element,Key>::~List(){
    //write
}






ListResult List<Element,Key>::insert(const Element &ele, const Key& key) {
    if(FindKeyAlreadyExists(key)){
        return NODE_ALREADY_EXISTS;
    }
    Node* ptr=new Node(ele,key);
    if(root== nullptr){
        root=ptr;
        root->left_son= nullptr;
        root->right_son= nullptr;
        root->parent= nullptr;
        root->hr=0;
        root->hl=0;
        return SUCCESS;
    }
    InsertNode(*ptr);

    return SUCCESS;

}










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










#endif //WET1_STRUCTS_LIST_H
