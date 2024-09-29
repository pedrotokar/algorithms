#include <iostream>
#include "sorting.h"
#include "selection.h"
#include <structs/Heaps.h>
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << " ]" << endl;}

using namespace std;

//Auxiliary algorithms
template <typename T> T findMedian(T[], int, int);

//Selection algorithms
template <typename T> T quickSearch(T[], int, int, int);
template <typename T> T MOMSearch(T[], int, int, int);

//Average case complexity: theta(n) - it's just n and not nlogn because the calls doesn't grow into a tree (counterintuitive but math says that)
//Worst case complexity: theta(n)
//Best case complexity: theta(n) - the last element is the one we are searching - calls partitionate only once
template <typename T>
T quickSearch(T vector[], int iStart, int iEnd, int iSearch){
    if (iEnd - iStart <= 0){
        cout << "Impossível buscar: array de tamanho inválido." << endl;
        return NULL;
    }
    if ((iSearch - iStart) >= (iEnd - iStart) || iSearch < 0){
        cout << "Impossível buscar, elemento inválido" << endl;
        return NULL;
    }
    int iPivot = partitionate(vector, iStart, iEnd - 1);
    if (iPivot == iSearch){
        return vector[iPivot];
    } else if (iPivot < iSearch){
        return quickSearch(vector, iPivot + 1, iEnd, iSearch);
    } else if (iPivot > iSearch){
        return quickSearch(vector, iStart, iPivot, iSearch);
    }
}

//Average case complexity: theta(nlogn) - same as quicksort just returns a number
//Worst case complexity: theta(n^2)
//Best case complexity: theta(nlogn)
template <typename T>
T findMedian(T vector[], int iStart, int iEnd){
    quickSort(vector, iStart, iEnd);
    return vector[iStart + (iEnd - iStart)/2];
}

//Average case complexity: theta(nlogn) - same as quicksort just returns a number
//Worst case complexity: theta(n^2)
//Best case complexity: theta(nlogn)
template <typename T>
T MOMSearch(T vector[], int iStart, int iEnd, int iSearch){
    if (iEnd - iStart <= 0){
        cout << "Impossível buscar: array de tamanho inválido." << endl;
        return NULL;
    }
    if ((iSearch - iStart) >= (iEnd - iStart) || iSearch < 0){
        cout << "Impossível buscar, elemento inválido" << endl;
        return NULL;
    }
    int iSize = (iEnd - iStart - 1)/5 + 1;
    T medians[iSize];
    int i = 0;
    for(i = 0; i < iSize - 1; i++){
        medians[i] = findMedian(vector, iStart + i * 5, iStart + (i + 1) * 5);
    }
    medians[i] = findMedian(vector, iStart + i * 5, iEnd);
    T MOM;
    if (i == 0){
        MOM = medians[0];
    } else {
        MOM = MOMSearch(medians, 0, i, i/2);
    }
    int iPivot = partitionate(vector, iStart, iEnd - 1, MOM);
    if (iPivot == iSearch){
        return vector[iPivot];
    } else if (iPivot < iSearch){
        return MOMSearch(vector, iPivot + 1, iEnd, iSearch);
    } else {
        return MOMSearch(vector, iStart, iPivot, iSearch);
    }
}


//Auxiliary algorithms
template int findMedian(int[], int, int);
template float findMedian(float[], int, int);

//Selection algorithms
template int quickSearch(int[], int, int, int);
template int MOMSearch(int[], int, int, int);
template float quickSearch(float[], int, int, int);
template float MOMSearch(float[], int, int, int);

int main(){
    float vector[] = {10.9, 2.3, 13, 6, 78, 9, 4, 3, 14, 39, 3, 1, 5, 12}; //14 elementos
    int intvector[] = {1, 2, 4, 2, 3, 4, 4, 2, 3, 1, 3, 4, 1, 2, 3, 4, 1, 3, 4, 1, 3, 4, 1, 2, 3, 4, 1, 4, 1, 3, 2,4 };
    printList(vector, 14);
    printList(intvector, 32);
    //cout << quickSearch(vector, 0, 14, 8) << endl;
    //cout << MOMSearch(vector, 0, 14, 9) << endl;
    printList(vector, 14);
    printList(intvector, 32);
  }
