//
// Created by User on 4/30/2020.
//
#define MAX(a, b) ((a > b) ? a : b)


#ifndef MIVNE_AVLTREE_H
#define MIVNE_AVLTREE_H

typedef enum AvlTreeResult_t{AVL_KEY_ALREADY_EXISTS,AVL_SUCCESS,AVL_ALLOCATION_ERROR
,AVL_KEY_DOESNT_EXISTS
}AvlTreeResult;

template <class Element,class Key>
class AvlTree {
private:
    class Node{
    public:
        Element& data;
        const Key& key;
        Node* right_son;
        Node* left_son;
        Node* parent;
        int hl;
        int hr;


        Node(const Element& data,const Key& key):data(*new Element(data)),key(*new Key(key)),right_son(nullptr)
                ,left_son(nullptr),parent(nullptr),hl(0),hr(0){};
        ~Node(){delete &data;};
        Node& operator=(const Node&)= default;
        //Node& operator=(Node&)= default;

        int getHeight(){return 1+MAX(hr,hl);};
        int getBalanceFactor();

        Node* getParent(){ return parent;};
        Node& getNodeFromKey(const Key key);
        Node* FindNext();
    };



    Node* root;
    Node* iterator;
    Node* first;
    void swapNodes(Node *node_to_del,Node* next_by_value);
    bool findKeyAlreadyExists(const Key& key);
    Node* removeBinarySearch(Node* node_to_del);
    void InsertNode(Node &newNode);
    void deleteAllNodes(Node* node);
    void Balance2(Node& starting_balance_node);
    void balanceAfterRemove(Node& parent_of_deleted);
    void rotateLeft(Node& node);
    void rotateRight(Node& node);
    void fixHeightAfterInsert(Node& inserted_node);
    void fixHeightAfterRemove(Node* parent_of_removed);
    void fixHeightAfterRotation(Node* rotated_node);


public:
    AvlTree():root(nullptr),iterator(nullptr),first(nullptr){};
    ~AvlTree();
    AvlTree& operator=(const AvlTree&)= default;
    AvlTreeResult insert (const Element& ele, const Key& key);
    AvlTreeResult remove (const Key& key);
    int getHeight(){ return root->getHeight();};
    Element* getElementptr(const Key& key);
    Element* getFirst();
    Element* getNext();
    const Key& getKey(){
        return iterator->key;
    }


};



template <class Element,class Key>
Element* AvlTree<Element,Key>::getFirst() {
    if(root== nullptr){
        return nullptr;
    }
    iterator=first;
    return &iterator->data;
}

//returns null ptr if iterator is null or iterator is on the largest node in the tree
template <class Element,class Key>
Element* AvlTree<Element,Key>::getNext() {
    if(iterator== nullptr){
        return nullptr;
    }
    if(iterator->right_son){
        iterator=iterator->right_son;
        while (iterator->left_son){
            iterator=iterator->left_son;
        }
        return &iterator->data;
    }
    while (iterator->parent &&iterator->parent->right_son==iterator){
        iterator=iterator->parent;
    }
    if(iterator->parent== nullptr){
        iterator=iterator->parent;
        return nullptr;
    }
    iterator=iterator->parent;
    return &iterator->data;

}


template <class Element,class Key>
Element* AvlTree<Element,Key>::getElementptr(const Key &key) {
    if(!findKeyAlreadyExists(key)){
        return nullptr;
    }
    Node& wanted=root->getNodeFromKey(key);
    return &wanted.data;


}

template <class Element,class Key>
void AvlTree<Element,Key>:: fixHeightAfterInsert(Node& inserted_node){
    inserted_node.hl=0;
    inserted_node.hr=0;
    Node* parent=inserted_node.parent;
    Node*  tmp=&inserted_node;
    while (parent!=nullptr){
        if(parent->left_son==tmp){
            parent->hl=tmp->getHeight();
        } else if(parent->right_son==tmp){
            parent->hr=tmp->getHeight();
        }
        tmp=parent;
        parent=tmp->parent;
    }
}


template <class Element,class Key>
void AvlTree<Element,Key>::fixHeightAfterRemove(Node* parent_of_removed) {
    if(!parent_of_removed){
        return;
    }
    Node* tmp=parent_of_removed;
    Node* parent=parent_of_removed->parent;
    if(parent_of_removed->right_son== nullptr){
        parent_of_removed->hr=0;
    } else{
        parent_of_removed->hr=parent_of_removed->right_son->getHeight();
    }
    if(parent_of_removed->left_son== nullptr){
        parent_of_removed->hl=0;
    } else{
        parent_of_removed->hl=parent_of_removed->left_son->getHeight();
    }
    while (parent!=nullptr){
        if(parent->left_son==tmp){
            parent->hl=tmp->getHeight();
        } else if(parent->right_son=tmp){
            parent->hr=tmp->getHeight();
        }
        tmp=parent;
        parent=tmp->parent;
    }

}

template <class Element,class Key>
void AvlTree<Element,Key>::fixHeightAfterRotation(Node* rotated_Node) {
    Node* tmp=rotated_Node->parent;
    while (tmp!= nullptr){
        if(tmp->left_son==rotated_Node){
            tmp->hl=rotated_Node->getHeight();
        }
        else{
            tmp->hr=rotated_Node->getHeight();
        }
        rotated_Node=tmp;
        tmp=rotated_Node->parent;
    }
}

template <class Element,class Key>
int AvlTree<Element,Key>::Node::getBalanceFactor() {
    if(!this){
        return 0;
    }
    if(this->right_son== nullptr){
        if(this->left_son== nullptr){
            return 0;
        }
        return left_son->getHeight();
    }
    if(this->left_son== nullptr){
        return -right_son->getHeight();
    }
    return left_son->getHeight()-right_son->getHeight();
}

//caleed only if we sure there is a node
template <class Element,class Key>
typename AvlTree<Element,Key>::Node&  AvlTree<Element,Key>::Node::getNodeFromKey(const Key key){
    Node* tmp=this;
    while (tmp!= nullptr){
        if(tmp->key==key){
            return *tmp;
        }
        if(tmp->key<key){
            tmp=(tmp->right_son);
        }
        else{
            tmp= (tmp->left_son);
        }
    }
}




template <class Element,class Key>
typename AvlTree<Element,Key>::Node* AvlTree<Element,Key>::Node::FindNext() {
    Node *nextByOrder=this->right_son;
    if(nextByOrder== nullptr){
        return this;
    }
    while(nextByOrder->left_son){
        nextByOrder=nextByOrder->left_son;
    }
    return nextByOrder;
}



template <class Element,class Key>
AvlTree<Element,Key>::~AvlTree(){
    if(root){
        deleteAllNodes(root);
    }
}

template <class Element,class Key>
void AvlTree<Element,Key>::deleteAllNodes(Node *node) {
    if(node){
        deleteAllNodes((node->right_son));
        deleteAllNodes((node->left_son));
        delete(node);
    }
}

template <class Element,class Key>
void AvlTree<Element,Key>::rotateLeft(AvlTree<Element, Key>::Node &node) {
    if(node.right_son== nullptr){
        return;
    }
    Node* B=node.right_son;
    Node* parent=node.parent;
    if(parent== nullptr){
        node.right_son=B->left_son;
        if(B->left_son){
            B->left_son->parent=&node;
        }
        B->left_son=&node;
        B->parent= nullptr;
        node.parent=B;
        node.hr=node.hl;
        B->hl++;
        root=B;
        return;
    }
    //else
    if(parent->right_son==&node){
        node.right_son=B->left_son;
        if(B->left_son){
            B->left_son->parent=&node;
        }
        B->left_son=&node;
        B->parent= parent;
        parent->right_son=B;
        node.parent=B;
        node.hr=node.hl;
        B->hl++;
        return;
    }
    node.right_son=B->left_son;
    if(B->left_son){
        B->left_son->parent=&node;
    }
    B->left_son=&node;
    B->parent= parent;
    parent->left_son=B;
    node.parent=B;
    node.hr=node.hl;
    B->hl++;
}

template <class Element,class Key>
void AvlTree<Element,Key>::rotateRight(AvlTree<Element, Key>::Node &node) {
    if(node.left_son== nullptr){
        return;
    }
    Node* A=node.left_son;
    Node*parent=node.getParent();
    if(parent== nullptr){
        node.left_son=A->right_son;
        if(A->right_son){
            A->right_son->parent=&node;
        }
        A->right_son=&node;
        A->parent= nullptr;
        node.parent=A;
        node.hl=node.hr;
        A->hr++;
        root=A;
        return;
    }
    //else
    if(parent->right_son==&node){
        node.left_son=A->right_son;
        if(A->right_son){
            A->right_son->parent=&node;
        }
        A->right_son=&node;
        A->parent=parent;
        parent->right_son=A;
        node.parent=A;
        node.hl=node.hr;
        A->hr++;
        return;
    }
    node.left_son=A->right_son;
    if(A->right_son){
        A->right_son->parent=&node;
    }
    A->right_son=&node;
    A->parent=parent;
    parent->left_son=A;
    node.parent=A;
    node.hl=node.hr;
    A->hr++;
}





template <class Element,class Key>
void AvlTree<Element,Key>::InsertNode(Node &newNode){
   if(root== nullptr){
        root=&newNode;
        return;
    }
    Node*tmp=root;
    while(tmp!= nullptr){
        if(tmp->key<newNode.key){
            if(tmp->right_son== nullptr){
                tmp->right_son=&newNode;
                newNode.parent=tmp;
                fixHeightAfterInsert(newNode);
                Balance2(newNode);
                return;
            }
            tmp=tmp->right_son;
        }
        else {
            if(tmp->left_son== nullptr){
                tmp->left_son=&newNode;
                newNode.parent=tmp;
                fixHeightAfterInsert(newNode);
                Balance2(newNode);
                //tmp->hl=tmp->hl+1;

                return;
            }
            tmp=tmp->left_son;

        }
    }


}

//deltes the nodde and returns a pointer to the father, null is such doesnt exists
template <class Element,class Key>
typename AvlTree<Element,Key>::Node* AvlTree<Element,Key>::removeBinarySearch(Node* node_to_del) {

    if(node_to_del->right_son!= nullptr &&node_to_del->left_son!=nullptr){
        Node* next_by_value=node_to_del->FindNext();
        swapNodes(node_to_del,next_by_value);
    }
    Node* parent=node_to_del->parent;


    if(parent== nullptr){//the tree has maximum 2 nodes
        if(node_to_del->right_son!= nullptr){
            node_to_del->right_son->parent= nullptr;
            root=node_to_del->right_son;
            delete(node_to_del);
            return root;
        } else if(node_to_del->left_son!= nullptr){
            node_to_del->left_son->parent= nullptr;
            root=node_to_del->left_son;
            delete(node_to_del);
            return root;
        } else{
            delete (node_to_del);
            root= nullptr;
            return nullptr;
        }

    }


    if(node_to_del->left_son==nullptr&& node_to_del->right_son== nullptr){//its a leaf
        if(parent->right_son==node_to_del){
            parent->right_son= nullptr;
            delete node_to_del;
            fixHeightAfterRemove(parent);
            return parent;
        }
        parent->left_son= nullptr;
        delete node_to_del;
        fixHeightAfterRemove(parent);
        return parent;
    }

    if(node_to_del->left_son== nullptr){//has only a right child
        if(parent->right_son==node_to_del){
            parent->right_son=node_to_del->right_son;
            node_to_del->right_son->parent=parent;
            delete node_to_del;
            fixHeightAfterRemove(parent);
            return parent;
        }
        parent->left_son=node_to_del->right_son;
        node_to_del->right_son->parent=parent;
        delete node_to_del;
        fixHeightAfterRemove(parent);
        return parent;
    }

    if(node_to_del->right_son== nullptr){//has only a left child

        if(parent->right_son==node_to_del){
            parent->right_son=node_to_del->left_son;
            node_to_del->left_son->parent=parent;
            delete node_to_del;
            fixHeightAfterRemove(parent);
            //parent->hr=parent->hr-1;
            return parent;
        }
        parent->left_son=node_to_del->left_son;
        node_to_del->left_son->parent=parent;
        delete node_to_del;
        fixHeightAfterRemove(parent);
        return parent;
    }
}

//we call the swap during just the removal
template <class Element,class Key>
void AvlTree<Element,Key>::swapNodes(Node* node_to_del,Node* next_by_value) {
    if(node_to_del==next_by_value){
        return;
    }
    if(node_to_del->right_son==next_by_value){
        next_by_value->left_son=node_to_del->left_son;
        if(next_by_value->left_son){
            next_by_value->left_son->parent=next_by_value;
        }
        next_by_value->hl=node_to_del->hl;
        node_to_del->hl=0;
        node_to_del->hr=next_by_value->hr;
        next_by_value->hr++;

        Node* parent=node_to_del->parent;
        node_to_del->parent=next_by_value;
        node_to_del->right_son=next_by_value->right_son;
        next_by_value->right_son=node_to_del;
        if(parent!= nullptr){
            next_by_value->parent=parent;
            if(parent->right_son==node_to_del){
                parent->right_son=next_by_value;
            } else if(parent->left_son==node_to_del){
                parent->left_son=next_by_value;
            }
            return;
        }
        else{
            next_by_value->parent= nullptr;
            return;
        }
    }
    next_by_value->hr=node_to_del->hr;
    next_by_value->hl=node_to_del->hl;
    Node *parent=next_by_value->getParent();
    parent->left_son=next_by_value->right_son;
    next_by_value->right_son=node_to_del->right_son;
    next_by_value->left_son=node_to_del->left_son;
    if(next_by_value->left_son){
        next_by_value->left_son->parent=next_by_value;
    }
    if(next_by_value->right_son){
        next_by_value->right_son->parent=next_by_value;
    }
    next_by_value->parent=node_to_del->parent;
    node_to_del->left_son= nullptr;
    node_to_del->right_son=parent->left_son;
    parent->left_son=node_to_del;
    node_to_del->parent=parent;
    if(next_by_value->parent== nullptr){
        root=next_by_value;
    }
    if(next_by_value->left_son==parent||next_by_value->right_son==parent){
        parent->parent=next_by_value;
    }
}




template <class Element,class Key>
void AvlTree<Element,Key>:: Balance2(Node& insertedNode){
   Node *p=insertedNode.parent;
   Node *tmp=&insertedNode;
   int balance_factor=0;
   while (tmp!=root){
       p=tmp->parent;

       balance_factor=p->getBalanceFactor();
       if(balance_factor==2){
           if(p->left_son->getBalanceFactor()<0){
               rotateLeft(*(p->left_son));
               fixHeightAfterRotation(p->left_son);
           }
           rotateRight(*p);
           fixHeightAfterRotation(p);
           return;
       }
       if(balance_factor==-2){
           if(p->right_son->getBalanceFactor()>0){
               rotateRight(*(p->right_son));
               fixHeightAfterRotation(p->right_son);
           }
           rotateLeft(*p);
           fixHeightAfterRotation(p);
           return;
       }
       tmp=tmp->parent;
   }

 }


template <class Element,class Key>
void AvlTree<Element,Key>::balanceAfterRemove(Node &parent_of_deleted) {
    Node *tmp=&parent_of_deleted;
    if(parent_of_deleted.right_son!= nullptr){
        tmp=parent_of_deleted.right_son;
    }
    else if(parent_of_deleted.left_son!= nullptr){
        tmp=parent_of_deleted.left_son;
    }
    Node *p=&parent_of_deleted;

    int balance_factor=0;
    while (tmp!=root){
        balance_factor=p->getBalanceFactor();
        if(balance_factor==2){
            if(p->left_son && p->left_son->getBalanceFactor()<0){
                rotateLeft(*(p->left_son));
                fixHeightAfterRotation(p->left_son);
            }
            rotateRight(*p);
            fixHeightAfterRotation(p);
        }
        else if(balance_factor==-2){
            if(p->right_son &&p->right_son->getBalanceFactor()>0){
                rotateRight(*(p->right_son));
                fixHeightAfterRotation(p->right_son);
            }
            rotateLeft(*p);
            fixHeightAfterRotation(p);
            return;
        }
        tmp=tmp->parent;
    }


}




//now its the functions of the tree

template <class Element,class Key>
bool AvlTree<Element,Key>::findKeyAlreadyExists(const Key& key){
    if(root== nullptr){
        return false;
    }
    Node *tmp2=root;

    while(tmp2!= nullptr){
        if(tmp2->key==key){
            return true;
        }
        if(tmp2->key<key){
            tmp2=tmp2->right_son;
        }
        else{
            tmp2=tmp2->left_son;
        }
    }
    return false;

}

template <class Element,class Key>
AvlTreeResult AvlTree<Element,Key>::insert(const Element &ele, const Key& key) {
    if(findKeyAlreadyExists(key)){
        return  AVL_KEY_ALREADY_EXISTS;
    }
    Node* ptr=new Node(ele,key);
    if(root== nullptr){
        root=ptr;
        root->left_son= nullptr;
        root->right_son= nullptr;
        root->parent= nullptr;
        root->hr=0;
        root->hl=0;
        first=root;
        return AVL_SUCCESS;
    }
    InsertNode(*ptr);
    if(key<first->key){
        first=ptr;
    }

    return AVL_SUCCESS;

}

template <class Element,class Key>
AvlTreeResult AvlTree<Element,Key>:: remove (const Key& key){
    if(!findKeyAlreadyExists(key)){
        return  AVL_KEY_DOESNT_EXISTS;
    }
    Node& node_to_del=root->getNodeFromKey(key);
    bool setFirst=(&node_to_del==first);
    Node* parent=removeBinarySearch(&node_to_del);

    //need toBalance

    if(parent== nullptr){
        return AVL_SUCCESS;
    }

    while (parent!= nullptr){

        balanceAfterRemove(*parent);
        parent=parent->parent;
    }
    if(setFirst){
        first=root;
        while (first &&first->left_son){
            first=first->left_son;
        }
    }
    return AVL_SUCCESS;
}

#endif //MIVNE_AVLTREE_H
