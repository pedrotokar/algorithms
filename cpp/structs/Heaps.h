#ifndef HeapsH
#define HeapsH

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

#endif
