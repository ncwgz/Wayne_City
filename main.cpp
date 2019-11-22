#include <iostream>
#include "minheap.h"
#include "redblacktree.h"

void testMinHeap();
void testRedBlackTree();

int main() {
    testRedBlackTree();
    return 0;
}

void testMinHeap()
{
    MinHeap<int> minHeap = MinHeap<int>();
    int arr[11] = {
            37, 58, 91, 12, 43, 5, 84, 68, 99, 77, 29
    };
    for (int i = 0; i < 11; ++i) {
        minHeap.insert(arr[i]);
        minHeap.print();
    }
    minHeap.increase(1, 100);
    minHeap.print();
    minHeap.removeMin();
    minHeap.print();
    minHeap.remove(4);
    minHeap.print();
    minHeap.removeMin();
    minHeap.print();
    minHeap.removeMin();
    minHeap.print();
    minHeap.removeMin();
    minHeap.print();
    minHeap.remove(2);
    minHeap.print();
    minHeap.remove(3);
    minHeap.print();
}

void testRedBlackTree()
{
    RedBlackTree<int, int> tree = RedBlackTree<int, int>();
//    for (int i = 1; i <= 10000; ++i) {
//        tree.insert(i, i*10);
//        std::cout<<i<<','<<i*10<<" Inserted:"<<std::endl;
//    }
//    int *to_remove = new int[1000]();
//    for (int k = 0; k < 1000; ++k) {
//        to_remove[k] = k * 2 + 1;
//    }
//    for (int j = 0; j < 1000; ++j) {
//        tree.remove(to_remove[j]);
//        std::cout<<to_remove[j]<<" removed: ======================================="<<std::endl;
//    }
    tree.insert(0, 100);
    tree.insert(0, 101);
    std::cout<<"???"<<std::endl;
}