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
    // Use an array to save nodes, the max length is 2000.
    T *HEAP_ARRAY = new int[2000];
    // Initial length is 0.
    int LENGTH = 0;

    // Bit
    inline int getParentIndex(int index) {
        return index >> 1;
    }

    inline int getLeftChildIndex(int index) {
        return index << 1;
    }

    inline int getRightChildIndex(int index) {
        return (index << 1) + 1;
    }

    inline T min(T t1, T t2) {
        if (t1 > t2) {
            return t2;
        } else {
            return t1;
        }
    }

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

    void print() {
        for (int i = 1; i <= LENGTH; ++i) {
            std::cout << HEAP_ARRAY[i] << ',';
        }
        std::cout << std::endl;
    }
};

