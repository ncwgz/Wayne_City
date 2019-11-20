//
// Created by wangguozhi on 2019-11-14.
//

#include <algorithm>
#include <iostream>

#ifndef WAYNE_CITY_MINHEAP_H
#define WAYNE_CITY_MINHEAP_H

#endif //WAYNE_CITY_MINHEAP_H

template<class T>
class MinHeap {
private:
    /* Use an array to save nodes, the max length is 1999.
     * The array starts with index of 1. The [0] is not used.
     * Because if index starts from 0, the bitwise operations
     * below will be a little more complex.
    */
    T *HEAP_ARRAY = new int[2000];
    // Initial length is 0.
    int LENGTH = 0;

    // Bitwise operations
    inline int getParentIndex(int index) {
        return index >> 1;
    }
    inline int getLeftChildIndex(int index) {
        return index << 1;
    }
    inline int getRightChildIndex(int index) {
        return (index << 1) + 1;
    }

    // Return the smaller (or equal) element between t1 and t2.
    inline T min(T t1, T t2) {
        if (t1 > t2) {
            return t2;
        } else {
            return t1;
        }
    }

    // Bottom-up heapify the heap after a new element has been appended.
    int heapifyUp(int index) {
        if (index == 1) {
            return 0;
        }
        int parent = getParentIndex(index);
        if (HEAP_ARRAY[index] < HEAP_ARRAY[parent]) {
            std::swap(HEAP_ARRAY[index], HEAP_ARRAY[parent]);
            heapifyUp(parent);
        } else {
            return index;
        }
    }

    // Top-down heapify the heap after remove some element.
    int heapifyDown(int index) {
        int left = getLeftChildIndex(index);
        int right = getRightChildIndex(index);
        if (right > LENGTH) {
            if (left > LENGTH) {
                return index;
            } else {
                if (HEAP_ARRAY[left] < HEAP_ARRAY[index]) {
                    std::swap(HEAP_ARRAY[left], HEAP_ARRAY[index]);
                } else {
                    return index;
                }
            }
        }
        if (min(HEAP_ARRAY[left], HEAP_ARRAY[right]) < HEAP_ARRAY[index]) {
            if (HEAP_ARRAY[right] < HEAP_ARRAY[left]) {
                std::swap(HEAP_ARRAY[right], HEAP_ARRAY[index]);
                heapifyDown(right);
            } else {
                std::swap(HEAP_ARRAY[left], HEAP_ARRAY[index]);
                heapifyDown(left);
            }
        } else {
            return index;
        }
    }

public:
    void insert(T &t) {
        HEAP_ARRAY[LENGTH + 1] = t;
        LENGTH++;
        heapifyUp(LENGTH);
    }

    void increase(int to_increase, int delta) {
        HEAP_ARRAY[to_increase] = HEAP_ARRAY[to_increase] + delta;
        heapifyDown(to_increase);
    }

    void remove(int to_remove) {
        std::swap(HEAP_ARRAY[to_remove], HEAP_ARRAY[LENGTH]);
        LENGTH--;
        heapifyDown(to_remove);
    }

    void removeMin() {
        std::swap(HEAP_ARRAY[1], HEAP_ARRAY[LENGTH]);
        LENGTH--;
        heapifyDown(1);
    }

    void print() {
        for (int i = 1; i <= LENGTH; ++i) {
            std::cout << HEAP_ARRAY[i] << ',';
        }
        std::cout << std::endl;
    }
};