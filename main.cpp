#include <iostream>
#include "minheap.h"

void testMinHeap();

int main() {
    testMinHeap();
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
    minHeap.increase(1, 55);
    minHeap.print();
    minHeap.remove(1);
    minHeap.print();
    minHeap.remove(4);
    minHeap.print();
    minHeap.remove(1);
    minHeap.print();
    minHeap.remove(1);
    minHeap.print();
    minHeap.remove(1);
    minHeap.print();
    minHeap.remove(1);
    minHeap.print();
    minHeap.remove(1);
    minHeap.print();
}