//
// Created by wangguozhi on 2019-11-21.
//

#include <algorithm>
#include <iostream>

#ifndef WAYNE_CITY_MINHEAP_H
#define WAYNE_CITY_MINHEAP_H

#endif //WAYNE_CITY_MINHEAP_H

template<class T>
class MinHeap {
private:
    /*
     * Use an array to save nodes, the max length is 2000
     * The array starts with index of 1. The [0] is not used.
     * Because if index starts from 0, the bitwise operations
     * below will be a little more complex
    */
    T** HEAP_ARRAY = new T*[2001];
    // Initial length is 0
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

    // Return the smaller element between t1 and t2
    inline T min(T t1, T t2) {
        if (t1 > t2) {
            return t2;
        } else {
            return t1;
        }
    }

    // Bottom-up heapify the heap after a new element has been appended
    int heapifyUp(int index) {
        if (index == 1) {
            return 0;
        }
        int parent = getParentIndex(index);
        if (*HEAP_ARRAY[index] < *HEAP_ARRAY[parent]) {
            std::swap(HEAP_ARRAY[index], HEAP_ARRAY[parent]);
            heapifyUp(parent);
        } else {
            return index;
        }
    }

    // Top-down heapify the heap after some element removed, or increased
    int heapifyDown(int index) {
        int left = getLeftChildIndex(index);
        int right = getRightChildIndex(index);
        if (right > LENGTH) {
            if (left > LENGTH) {
                return index;
            } else {
                if (*HEAP_ARRAY[left] < *HEAP_ARRAY[index]) {
                    std::swap(HEAP_ARRAY[left], HEAP_ARRAY[index]);
                    return left;
                } else {
                    return index;
                }
            }
        }
        if (min(*HEAP_ARRAY[left], *HEAP_ARRAY[right]) < *HEAP_ARRAY[index]) {
            if (*HEAP_ARRAY[right] < *HEAP_ARRAY[left]) {
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
    // Insert element t into the heap
    void insert(T *&t) {
        HEAP_ARRAY[LENGTH + 1] = t;
        LENGTH++;
        heapifyUp(LENGTH);
    }

    // Increase delta to the element with tindex of to_increase
    int increase(int to_increase, int delta) {
        *HEAP_ARRAY[to_increase] = *HEAP_ARRAY[to_increase] + delta;
        return heapifyDown(to_increase); // Heapify down after increasing
    }

    // Remove the element with index of to_remove.
    void remove(int to_remove) {
        std::swap(HEAP_ARRAY[to_remove], HEAP_ARRAY[LENGTH]); // Swap it with the last element
        LENGTH--;
        heapifyDown(to_remove); // Heapify down after removing
    }

    // Remove the element t
    void removeElement(T t) {
        int toRemove = getIndexByElement(t); // Get the index of the element
        remove(toRemove);
    }

    // Get the index of the element t
    int getIndexByElement(T t) {
        // Linear search
        for (int i = 1; i <= LENGTH; ++i) {
            if (*HEAP_ARRAY[i] == t) {
                return i;
            }
        }
    }

    // Get the size of the heap
    int getLength() {
        return this->LENGTH;
    }

    // Get the element with the index of index
    T getElement(int index) {
        return *HEAP_ARRAY[index];
    }

    // Get the pointer of the element with the index of index
    T* getElementPointer(int index) {
        return this->HEAP_ARRAY[index];
    }
};