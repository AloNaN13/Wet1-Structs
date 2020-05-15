

#include "AVLTree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>


#define addNode insert
#define removeNode remove

#include "AvlTree.h"
#include "AVL_tests.h"

int main(){
    //AVL_Basics();
    AVL_TESTS();

    /*
    AvlTree<int, int> tree;

    std::vector<int> vector;
    for (int i=1; i<=20; i++) vector.push_back(i);
           printf("i\n");

    //Randomly insert and removes nodes
    for (int k = 0; k < 20; ++k) {
        printf("%d\n",k);
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            tree.addNode(*it,*it);

        }
        //tree.printTree();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            tree.removeNode(*it);
            //tree.printTree();

        }
        tree.clear();
    }
    return 0;*/
}

