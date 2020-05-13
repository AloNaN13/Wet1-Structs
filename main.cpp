#include <iostream>
#include "AvlTree.h"
#include <cassert>


int main() {
    std::cout << "Hello, World!" << std::endl;
    //AVL_Basics();

    int arr[9];
    for(int i=0;i<9;i++){
        arr[i]=i;
    }
    AvlTree <int ,int> sari(arr,arr,9);
    printf("gello");




    return 0;
}