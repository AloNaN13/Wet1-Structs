#include <iostream>
#include "AvlTree.h"
#include <cassert>
#include "AVL_tests.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    //AVL_Basics();

    AvlTree <int,int> tree;
    AvlTreeResult result;

    for(int i=0;i<1000;i++)
    {
        result=tree.insert(i,i);
        assert(result==SUCCESS);
    }

    for (int i = 0; i <1000 ; ++i) {
        printf("%d, \n",i);
        result=tree.remove(i);
        assert((result==SUCCESS));
    }
   




    return 0;
}