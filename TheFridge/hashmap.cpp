//merge sort
#include <iostream>
#include <vector>

using namespace std;

class MergeSort {
    vector<int> merge(vector<int> attribute, int start, int middle, int end) {
        int leftSize = middle - start + 1;
        int rightSize = end - middle;

// Separate halves into two seperate sorted arrays
        //int left[leftSize], right[rightSize];
        vector<int> sortedLeft(leftSize);
        vector<int> sortedRight(rightSize);
        for(int i=0; i < leftSize; i++){
            sortedLeft[i] = attribute[start + i];
        }
        for(int i=0; i < rightSize; i++){
            sortedRight[i] = attribute[middle + 1 + i];
        }

// Pointers for merging
        int leftPtr = 0, rightPtr = 0;
        int mergedPtr = start;

// While both left and right have elements left
        while (leftPtr < leftSize && rightPtr < rightSize) {
            if (sortedLeft[leftPtr] <= sortedRight[rightPtr]) {
                attribute[mergedPtr++] = sortedLeft[leftPtr++];
            }
            else {
                attribute[mergedPtr++] = sortedRight[rightPtr++];
            }
        }

        while (leftPtr < leftSize) { // While left has elements left
            attribute[mergedPtr++] = sortedLeft[leftPtr++];
        }

        while (rightPtr < rightSize) { // While right has elements left
            attribute[mergedPtr++] = sortedRight[rightPtr++];
        }
    }

    void mergeSort(vector<int> attribute, int start, int end) {
        if (start < end) { //basically if there is more than 1 element in the vector
            int middle = (start + end) / 2;  //get the middle index
            mergeSort(attribute, start, middle); //divide the first half until it is ones
            mergeSort(attribute, middle + 1, end); //then divide the second half
            merge(attribute, start, middle, end); //then conquer starting with the first element
        }
    }
};
