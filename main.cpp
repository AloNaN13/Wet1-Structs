#include <iostream>
#include "AvlTree.h"
#include <cassert>
#include "AVL_tests.h"
#include "Artist.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    //AVL_Basics();
    AvlTree <int ,int> sari;
    for(int i=0;i<1000;i++){
        sari.insert(i,i);
    }

    for(int i=0;i<1000;i++){
        sari.remove(i);
    }
    printf("");




    return 0;
}