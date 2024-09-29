//Although heaps in the algorithms aren't represented by a special structure, but
//by a array with special ordering, I thought that it would be better to put
//all the associated functions into this file rather than in the sorting file
//(where currently it's the only place that heaps are used)

#include "Heaps.h"

template <typename T> void swap(T[], int, int);
template <typename T> void maxHeapify(T[], int, int);
template <typename T> void minHeapify(T[], int, int);
template <typename T> void buildMaxHeap(T[], int);
template <typename T> void buildMinHeap(T[], int);

template <typename T>
void swap(T vector[], int i, int j){
    T temp = vector[i];
    vector[i] = vector[j];
    vector[j] = temp;
}

//Average case complexity: O(logn) - descends in the heap until isn't needed anymore - does theta(1) operations
//Worst case complexity: O(logn) - descends all the way down to the leaves
//Best case complexity: O(1) - doesn't descent at all
template <typename T>
void maxHeapify(T vector[], int iIndex, int iLength){
    int i = iIndex;
    int iLeft = 2 * iIndex + 1; //+1 because arrays are 0-indexed
    int iRight = 2 * iIndex + 2;
    if (iLeft < iLength && vector[i] < vector[iLeft]){
        i = iLeft;
    }
    if (iRight < iLength && vector[i] < vector[iRight]){
        i = iRight;
    }
    if (i != iIndex){
        swap(vector, i, iIndex);
        maxHeapify(vector, i, iLength);
    }
}

//Average case complexity: O(logn) - Same as above just change comparisons
//Worst case complexity: O(logn)
//Best case complexity: O(1)
template <typename T>
void minHeapify(T vector[], int iIndex, int iLength){
    int i = iIndex;
    int iLeft = 2 * iIndex + 1; //+1 because arrays are 0-indexed
    int iRight = 2 * iIndex + 2;
    if (iLeft < iLength && vector[i] >= vector[iLeft]){
        i = iLeft;
    }
    if (iRight < iLength && vector[i] >= vector[iRight]){
        i = iRight;
    }
    if (i != iIndex){
        swap(vector, i, iIndex);
        minHeapify(vector, i, iLength);
    }
}

//Average case complexity: O(n) - doing the summation of the costs retrieve this result
//Worst case complexity: O(n)
//Best case complexity: O(n) - heap is already done - maxHeapify doesnt do nothing
template <typename T>
void buildMaxHeap(T vector[], int iLength){
    for (int i = iLength/2 - 1; i >= 0; i--){
        maxHeapify(vector, i, iLength);
    }
}

//Average case complexity: O(n) - same as above just change heap type
//Worst case complexity: O(n)
//Best case complexity: O(n)
template <typename T>
void buildMinHeap(T vector[], int iLength){
    for (int i = iLength/2 - 1; i >= 0; i--){
        minHeapify(vector, i, iLength);
    }
}

template void swap(float[], int, int);
template void maxHeapify(float[], int, int);
template void minHeapify(float[], int, int);
template void buildMaxHeap(float[], int);
template void buildMinHeap(float[], int);
template void swap(int[], int, int);
template void maxHeapify(int[], int, int);
template void minHeapify(int[], int, int);
template void buildMaxHeap(int[], int);
template void buildMinHeap(int[], int);
