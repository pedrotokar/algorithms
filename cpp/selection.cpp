#include <iostream>
#include "sorting.h"
#include "selection.h"
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << " ]" << endl;}

using namespace std;

//Auxiliary algorithms
template <typename T> T findMedian(T[], int, int);

//Selection algorithms
template <typename T> T quickSelect(T[], int, int, int);
template <typename T> T MOMSelect(T[], int, int, int);

//Average case complexity: theta(n) - it's just n and not nlogn because the calls doesn't grow into a tree (counterintuitive but math says that)
//Worst case complexity: theta(n)
//Best case complexity: theta(n) - the last element is the one we are searching - calls partitionate only once
template <typename T>
T quickSelect(T vector[], int iStart, int iEnd, int iSearch){
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
        return quickSelect(vector, iPivot + 1, iEnd, iSearch);
    } else {
        return quickSelect(vector, iStart, iPivot, iSearch);
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
T MOMSelect(T vector[], int iStart, int iEnd, int iSearch){
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
        MOM = MOMSelect(medians, 0, i, i/2);
    }
    int iPivot = partitionate(vector, iStart, iEnd - 1, MOM);
    if (iPivot == iSearch){
        return vector[iPivot];
    } else if (iPivot < iSearch){
        return MOMSelect(vector, iPivot + 1, iEnd, iSearch);
    } else {
        return MOMSelect(vector, iStart, iPivot, iSearch);
    }
}

//Auxiliary algorithms
template int findMedian(int[], int, int);
template float findMedian(float[], int, int);

//Selection algorithms
template int quickSelect(int[], int, int, int);
template int MOMSelect(int[], int, int, int);
template float quickSelect(float[], int, int, int);
template float MOMSelect(float[], int, int, int);

// int main(){
//     float vector[] = {10.9, 2.3, 13, 6, 78, 9, 4, 3, 14, 39, 3, 1, 5, 12}; //14 elementos
//     int intvector[] = {1, 2, 4, 2, 3, 4, 4, 2, 3, 1, 3, 4, 1, 2, 3, 4, 1, 3, 4, 1, 3, 4, 1, 2, 3, 4, 1, 4, 1, 3, 2,4 };
//     int biggervector[] = {10, 2, 13, 6, 78, 9, 4, 3, 14, 39, 3, 1, 5, 12, 2, 6, 34 ,13, 98,2, 3,48, 17, 2,8, 23,47 };
//     int temp[] = {1, 1, 2, 5, 20, 21};
//     //printList(vector, 14);
//     //printList(intvector, 32);
//     printList(biggervector, 27);
//     //cout << quickSelect(vector, 0, 14, 8) << endl;
//     //cout << MOMSelect(biggervector, 0, 27, 9) << endl;
//     //cout << ex10(biggervector, 0, 27, 27) << endl;
//     //cout << ex10(temp, 0, 6, 6) << endl;
//     //quickSort(biggervector, 0, 27);
//     //printList(vector, 14);
//     //printList(intvector, 32);
//     printList(biggervector, 27);
// }
