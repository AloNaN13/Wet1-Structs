//
// Created by User on 5/8/2020.
//

#ifndef WET1_STRUCTS_LIST_H
#define WET1_STRUCTS_LIST_H


#include "AvlTree.h"







template <class Element,class Key>
class List{
private:
    class ListNode{
    public:
        Key& key;
        Element& data;
        ListNode* prev_node;
        ListNode* next_node;

        Node(const Element& data,const Key& key):data(data),key(key),right_son(nullptr)
                ,left_son(nullptr),parent(nullptr),hl(0),hr(0){};

        ListNode(Key& key, Element& data): key(key), data(data), prev_node(nullptr),
                next_node(nullptr){};
        ~ListNode() = default;
        ListNode(const ListNode& node) = delete;
        ListNode& operator=(const ListNode& node) = delete;

        ListNode* getPrevNode() { return this.prev_node;};
        ListNode* getNextNode() { return this.next_node;};
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


};



List::~List(){
    //write
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
