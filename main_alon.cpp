/*
 * testAVLTree.cpp
 *
 *  Created on: 19 ���� 2013
 *      Author: shirel
 */

#include "AVLTree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>

#include "MusicManger_sari_tests.h"



#define addNode insert
#define removeNode remove


int main(){
    MusicMangerTest();
    return 0;
}


//AVITALS

/*
int main(){
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
    return 0;
}

*/