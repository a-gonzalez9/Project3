//
// Created by carme on 11/28/2024.
//

#include "heap.h"
#include <iostream>
using namespace std;
class Heap {
public:
    void heapifyDown(int index, int size, int arr[]) {
        // swap root node with smallest child until valid heap
        int leftChild = 2*index + 1;
        int rightChild = 2*index + 2;
        int biggerKid;
        if (index*2 + 1 >= size) {
            return;
        }
        else if (2*index + 1 == size - 1) {
            if (leftChild < index) {
                return;
            }
            else {
                biggerKid = leftChild;
            }
        }
        else {
            if (arr[leftChild] < arr[index] && arr[rightChild] < arr[index]) {
                return;
            }
            else if (arr[leftChild] > arr[index] && arr[rightChild] > arr[index]) {
                //find bigger child
                if (arr[leftChild] > arr[rightChild]) {
                    biggerKid = leftChild;
                }
                else{
                    biggerKid = rightChild;
                }
            }
        }
        //swap node at index with biggerKid
        swap(arr[index], arr[biggerKid]);
        heapifyDown(biggerKid, size, arr);
    }

    void buildMaxHeap(int arr[], int size) {

        for (int i = (size / 2) - 1; i >= 0; i--) {
            heapifyDown(i, size, arr);
        }

    }
};