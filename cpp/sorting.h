#ifndef sortingH
#define sortingH

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

#endif



