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
template <typename T> void maxHeapify(int[], int, int, T[]);
template <typename T> void minHeapify(int[], int, int, T[]);
template <typename T> void maxHeapifyBottom(int[], int, int, T[]);
template <typename T> void minHeapifyBottom(int[], int, int, T[]);
template <typename T> void buildMaxHeap(int[], int, T[]);
template <typename T> void buildMinHeap(int[], int, T[]);


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
void maxHeapify(T heap[], int iIndex, int iLength){
    int i = iIndex;
    int iLeft = 2 * iIndex + 1; //+1 because arrays are 0-indexed
    int iRight = 2 * iIndex + 2;
    if (iLeft < iLength && heap[i] < heap[iLeft]){
        i = iLeft;
    }
    if (iRight < iLength && heap[i] < heap[iRight]){
        i = iRight;
    }
    if (i != iIndex){
        swap(heap, i, iIndex);
        maxHeapify(heap, i, iLength);
    }
}

//Average case complexity: O(logn) - Same as above just change comparisons
//Worst case complexity: O(logn)
//Best case complexity: O(1)
template <typename T>
void minHeapify(T heap[], int iIndex, int iLength){
    int i = iIndex;
    int iLeft = 2 * iIndex + 1; //+1 because arrays are 0-indexed
    int iRight = 2 * iIndex + 2;
    if (iLeft < iLength && heap[i] >= heap[iLeft]){
        i = iLeft;
    }
    if (iRight < iLength && heap[i] >= heap[iRight]){
        i = iRight;
    }
    if (i != iIndex){
        swap(heap, i, iIndex);
        minHeapify(heap, i, iLength);
    }
}

//Average case complexity: O(n) - doing the summation of the costs retrieve this result
//Worst case complexity: O(n)
//Best case complexity: O(n) - heap is already done - maxHeapify doesnt do nothing
template <typename T>
void buildMaxHeap(T heap[], int iLength){
    for (int i = iLength/2 - 1; i >= 0; i--){
        maxHeapify(heap, i, iLength);
    }
}

//Average case complexity: O(n) - same as above just change heap type
//Worst case complexity: O(n)
//Best case complexity: O(n)
template <typename T>
void buildMinHeap(T heap[], int iLength){
    for (int i = iLength/2 - 1; i >= 0; i--){
        minHeapify(heap, i, iLength);
    }
}

//The same algorithms, but now the value is acessed in a array
//The vector which represents the heap is now an int, since its values
//will be used to acess the true values array
template <typename T>
void maxHeapify(int heap[], int iIndex, int iLength, T values[]){
    int i = iIndex;
    int iLeft = 2 * iIndex + 1; //+1 because arrays are 0-indexed
    int iRight = 2 * iIndex + 2;
    if (iLeft < iLength && values[heap[i]] < values[heap[iLeft]]){
        i = iLeft;
    }
    if (iRight < iLength && values[heap[i]] < values[heap[iRight]]){
        i = iRight;
    }
    if (i != iIndex){
        swap(heap, i, iIndex);
        maxHeapify(heap, i, iLength, values);
    }
}

//Average case complexity: O(logn) - Same as above just change comparisons
//Worst case complexity: O(logn)
//Best case complexity: O(1)
template <typename T>
void minHeapify(int heap[], int iIndex, int iLength, T values[]){
    int i = iIndex;
    int iLeft = 2 * iIndex + 1; //+1 because arrays are 0-indexed
    int iRight = 2 * iIndex + 2;
    if (iLeft < iLength && values[heap[i]] >= values[heap[iLeft]]){
        i = iLeft;
    }
    if (iRight < iLength && values[heap[i]] >= values[heap[iRight]]){
        i = iRight;
    }
    if (i != iIndex){
        swap(heap, i, iIndex);
        minHeapify(heap, i, iLength, values);
    }
}

template <typename T>
void maxHeapifyBottom(int heap[], int iLength, int iIndex, T values[]) {
    int iParent = (iIndex - 1) / 2;
    if (iParent >= 0) { //If negative means it's the top of the heap
        if (values[heap[iIndex]] > values[heap[iParent]]) {
            swap(heap, iIndex, iParent);
            // Recursively heapify the parent node
            maxHeapifyBottom(heap, iLength, iParent, values);
        }
    }
}

template <typename T>
void minHeapifyBottom(int heap[], int iLength, int iIndex, T values[]) {
    int iParent = (iIndex - 1) / 2;
    if (iParent >= 0) { //If negative means it's the top of the heap
        if (values[heap[iIndex]] <= values[heap[iParent]]) {
            swap(heap, iIndex, iParent);
            // Recursively heapify the parent node
            minHeapifyBottom(heap, iLength, iParent, values);
        }
    }
}

//Average case complexity: O(n) - doing the summation of the costs retrieve this result
//Worst case complexity: O(n)
//Best case complexity: O(n) - heap is already done - maxHeapify doesnt do nothing
template <typename T>
void buildMaxHeap(int heap[], int iLength, T values[]){
    for (int i = iLength/2 - 1; i >= 0; i--){
        maxHeapify(heap, i, iLength, values);
    }
}

//Average case complexity: O(n) - same as above just change heap type
//Worst case complexity: O(n)
//Best case complexity: O(n)
template <typename T>
void buildMinHeap(int heap[], int iLength, T values[]){
    for (int i = iLength/2 - 1; i >= 0; i--){
        minHeapify(heap, i, iLength, values);
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
template void maxHeapify(int[], int, int, int[]);
template void minHeapify(int[], int, int, int[]);
template void maxHeapifyBottom(int[], int, int, int[]);
template void minHeapifyBottom(int[], int, int, int[]);
template void buildMaxHeap(int[], int, int[]);
template void buildMinHeap(int[], int, int[]);
template void maxHeapify(int[], int, int, float[]);
template void minHeapify(int[], int, int, float[]);
template void maxHeapifyBottom(int[], int, int, float[]);
template void minHeapifyBottom(int[], int, int, float[]);
template void buildMaxHeap(int[], int, float[]);
template void buildMinHeap(int[], int, float[]);
