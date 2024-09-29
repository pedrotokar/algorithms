#include <iostream>
#include "sorting.h"
#include <structs/Heaps.h>
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << " ]" << endl;}

using namespace std;

//Auxiliary algorithms
template <typename T> void swap(T[], int, int);
template <typename T> void mergeArrays(T[], int, int);
template <typename T> int partitionate(T[], int, int);
template <typename T> int partitionate(T[], int, int, T);

//Sorting algorithms
template <typename T> void bubbleSort(T[], int);
template <typename T> void selectionSort(T[], int);
template <typename T> void insertionSort(T[], int);
template <typename T> void mergeSort(T[], int, int);
template <typename T> void quickSort(T[], int, int);
template <typename T> void heapSort(T[], int);
void countingSort(int[], int, int);

//Average case complexity: theta(1) - does 3 instructions every time
//Worst case complexity: theta(1)
//Best case complexity: theta(1)
template <typename T>
void swap(T vector[], int i, int j){
    T temp = vector[i];
    vector[i] = vector[j];
    vector[j] = temp;
}

//Average case complexity: theta(n^2)
//Worst case complexity: theta(n^2)
//Best case complexity: theta(n^2)
template <typename T>
void bubbleSort(T vector[], int iLength){
    if (iLength <= 1){
        cout << "Impossível ordenar: array de tamanho inválido." << endl;
        return;
    }

    bool bUnordered;
    for (int i = 0; i < iLength; i++){
        bUnordered = false;
        for (int j = 0; j < iLength - 1; j++){
            if (vector[j] > vector[j + 1]){
                swap(vector, j, j + 1);
                bUnordered = true;
            }
        }
        if (bUnordered == false) break;
    }
}

//Average case complexity: theta(n^2)
//Worst case complexity: theta(n^2)
//Best case complexity: theta(n^2)
template <typename T>
void selectionSort(T vector[], int iLength){
    if (iLength <= 1){
        cout << "Impossível ordenar: array de tamanho inválido." << endl;
        return;
    }

    for (int i = 0; i < iLength - 1; i++){
        int minIndex = i;
        for(int j = i; j < iLength; j++){
            if(vector[j] < vector[minIndex]){
                minIndex = j;
            }
        }
        swap(vector, i, minIndex);
    }
}

//Average case complexity: theta(n^2)
//Worst case complexity: theta(n^2)
//Best case complexity: theta(n)
template <typename T>
void insertionSort(T vector[], int iLength){
    if (iLength <= 1){
        cout << "Impossível ordenar: array de tamanho inválido." << endl;
        return;
    }

    for (int i = 1; i < iLength; i++){
        T moving = vector[i];
        int j;
        for (j = i - 1; j >= 0 && vector[j] > moving; j--){
            vector[j + 1] = vector[j];
        }
        vector[j + 1] = moving;
    }
}

//Average case complexity: theta(n) - runs trought every element of the two arrays
//Worst case complexity: theta(n)
//Best case complexity: theta(n)
template <typename T>
void mergeArrays(T vector[], int iStart, int iEnd){
    int iMid = iStart + (iEnd - iStart)/2;
    T vector2[iEnd - iStart];
    int iPosLeft = iStart;
    int iPosRight = iMid;
    int iPosNew = 0;
    while (iPosLeft < iMid && iPosRight < iEnd){
        if(vector[iPosLeft] <= vector[iPosRight]){
            vector2[iPosNew] = vector[iPosLeft];
            iPosNew++; iPosLeft++;
        } else {
            vector2[iPosNew] = vector[iPosRight];
            iPosNew++; iPosRight++;
        }
    }
    while (iPosLeft < iMid){
        vector2[iPosNew] = vector[iPosLeft];
        iPosLeft++; iPosNew++;
    }
    while (iPosRight < iEnd){
        vector2[iPosNew] = vector[iPosRight];
        iPosRight++; iPosNew++;
    }
    for (int i = iStart; i < iEnd; i++){
        vector[i] = vector2[i - iStart];
    }
}

//Average case complexity: theta(nlogn) - each use has theta(n) and it's in a tree
//Worst case complexity: theta(nlogn)
//Best case complexity: theta(nlogn)
template <typename T>
void mergeSort(T vector[], int iStart, int iEnd){
    if (iStart < iEnd - 1){
        int iMid = iStart + (iEnd - iStart)/2;
        mergeSort(vector, iStart, iMid);
        mergeSort(vector, iMid, iEnd);
        mergeArrays(vector, iStart, iEnd);
    }
}

//Average case complexity: theta(n) - runs trought every element till the last
//Worst case complexity: theta(n) - always runs independent of the vector configuration
//Best case complexity: theta(n)
template <typename T>
int partitionate(T vector[], int iStart, int iLast){
    int j = iStart;
    for (int i = iStart; i < iLast; i++){
        if (vector[i] <= vector[iLast]){
            swap(vector, i, j);
            j++;
        }
    }
    swap(vector, j, iLast);
    return j;
}

//Average case complexity: theta(n) - do theta(n) search then calls another theta(n) algorithm just one time
//Worst case complexity: theta(n) - independent of the search, will do theta(n) partitionate
//Best case complexity: theta(n)
template <typename T>
int partitionate(T vector[], int iStart, int iLast, T iPartition){ //Envelops above function and do a search before calling it - TODO: maybe can reduce operations needed in future
    int j = -1;
    for (int i = iStart; i <= iLast; i++){
        if (vector[i] == iPartition){
            j = i;
            break;
        }
    }
    if(j == -1) return -1;
    swap(vector, j, iLast);
    return partitionate(vector, iStart, iLast);
}


//Average case complexity: theta(nlogn) - constant greater than best case
//Worst case complexity: theta(n^2) - happens when pivots are in the beggining or end of lists
//Best case complexity: theta(nlogn) - happens when pivots are in the half of the lists
template <typename T>
void quickSort(T vector[], int iStart, int iEnd){
    while (iStart < iEnd - 1){
        int iMid = partitionate(vector, iStart, iEnd - 1);
        if (iMid - iStart < iEnd - iMid) { //Computing the shortest first, then goes back and computes the greater (withouth needing to call the function two times)
            quickSort(vector, iStart, iMid);
            iStart = iMid;
        } else {
            quickSort(vector, iMid, iEnd);
            iEnd = iMid;
        }
    }
}

//Average case complexity: theta(nlogn) - O(n) + does logn operations through all the array (O(nlogn))
//Worst case complexity: theta(nlogn)
//Best case complexity: theta(nlogn) - always swap entries and redo the heap
template <typename T>
void heapSort(T vector[], int iLength){
    if (iLength <= 1){
        cout << "Impossível ordenar: array de tamanho inválido." << endl;
        return;
    }
    buildMaxHeap(vector, iLength);
    for (int i = iLength - 1; i > 0; i--){
        swap(vector, 0, i);
        maxHeapify(vector, 0, i);
    }
}

/* //TODO: implement
 t e*mplate <typename T>
 void mergeMultiple(T vectors[], int iLengths[], int iCount){
 int iSize = 0;
 for(int i = 0; i < iCount; i++) iSize = iSize + iLengths[i];
 //int iSize = iCount * iLength;
 T sortedVector[iSize];
 T auxiliary[iCount];
 for (int i = 0; i < iCount; i++){
     for (int j = 0; j < iLengths[i]; j++){
         //float temp = vectors[i *iLength + j];
         //sortedVector[iLength * i + j] = &temp;
         }
         printList(sortedVector, iSize);
         }
         }
         */

//Average case complexity: theta(n) iters through vector and aux array k a fixed number of times - actually it's theta(n + k)
//Worst case complexity: theta(n)
//Best case complexity: theta(n)
void countingSort(int vector[], int iLength, int k){ //Not a template cause the algorithm works only with integers
    int iFreqs[k + 1];
    int iOrdered[iLength];
    for (int i = 0; i < k + 1; i++){ //This arrays needs to start with only zeros
        iFreqs[i] = 0;
    }
    for (int i = 0; i < iLength; i++){
        iFreqs[vector[i] + 1]++;
    }
    for (int i = 0; i < k; i++){
        iFreqs[i + 1] = iFreqs[i] + iFreqs[i + 1];
    }
    for (int i = 0; i <iLength; i++){
        int j = vector[i];
        iOrdered[iFreqs[j]] = vector[i];
        iFreqs[j]++;
    }
    for (int i = 0; i < iLength; i++){
        vector[i] = iOrdered[i];
    }
}

//Auxiliary algorithms
template void swap(int[], int, int);
template void mergeArrays(int[], int, int);
template int partitionate(int[], int, int);
template int partitionate(int[], int, int, int);
template void swap(float[], int, int);
template void mergeArrays(float[], int, int);
template int partitionate(float[], int, int);
template int partitionate(float[], int, int, float);

//Sorting algorithms
template void bubbleSort(int[], int);
template void selectionSort(int[], int);
template void insertionSort(int[], int);
template void mergeSort(int[], int, int);
template void quickSort(int[], int, int);
template void heapSort(int[], int);
template void bubbleSort(float[], int);
template void selectionSort(float[], int);
template void insertionSort(float[], int);
template void mergeSort(float[], int, int);
template void quickSort(float[], int, int);
template void heapSort(float[], int);

//TODO: decidir padrão pra entrada de todos (com intervalos? sem? usando referencias?)

// int main(){
//     float vector[] = {10.9, 2.3, 3, 6, 78, 9, 4, 3, 14, 39, 3, 1, 5, 12}; //14 elements
//     int intvector[] = {1, 2, 4, 2, 3, 4, 4, 2, 3, 1, 3, 4, 1, 2, 3, 4, 1, 3, 4, 1, 3, 4, 1, 2, 3, 4, 1, 4, 1, 3, 2,4 }; //32 elements
//     float vectors[18] = {2, 3, 4, 20, 21,
//                          1, 3, 12,
//                          1, 10, 11, 12, 13, 14,
//                          9, 12, 13, 15};
//     int lengths[4] = {5, 3, 6, 4};
//
//     printList(vector, 14);
//     printList(intvector, 32);
//     //bubbleSort(vector, 14);
//     //selectionSort(vector, 14);
//     //insertionSort(vector, 14);
//     //mergeSort(vector, 0, 14);
//     //quickSort(v, 0, 14);
//     //heapSort(vector, 14);
//     //mergeMultiple(vectors, lengths, 4);
//     //countingSort(intvector, 32, 4);
//     printList(vector, 14);
//     printList(intvector, 32);
// }
