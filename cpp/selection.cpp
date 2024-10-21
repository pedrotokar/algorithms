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
        return NULL; //Returns null because returning any type of number may be misleading. If I ever implement that in Rust, things will be much safer (and bloated too)
    }
    if ((iSearch - iStart) >= (iEnd - iStart) || iSearch < 0){
        cout << "Impossível buscar, elemento inválido" << endl;
        return NULL;
    }
    int iPivot = partitionate(vector, iStart, iEnd);
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
T findMedian(T vector[], int iStart, int iEnd){ //The length will always be an odd number, so the median exists and isn't the mean of two numbers
    quickSort(vector, iStart, iEnd);
    return vector[iStart + (iEnd - iStart)/2];
}

//Average case complexity: theta(n) - since all the sorts are done in very small arrays and into subarrays, the cost of each call is linear. Since it always splits the array, the total cost is linear too
//Worst case complexity: theta(n)
//Best case complexity: theta(n)
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
    int iPivot = partitionateByElement(vector, iStart, iEnd, MOM);
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

/*int main(){
    cout << "Quick Select" << endl;
    float vector[] = {10.9, -2.3, 3, 6.12, 78, -9, 4, 3, -14, 39, 3, 1, 5.45, 12, -19,4, 0, -1, 1, 9, 12.9}; //21 elements
    printList(vector, 21);
    cout << "elemento 0: " << quickSelect(vector, 0, 21, 0) << endl;
    cout << "elemento 11: " << quickSelect(vector, 0, 21, 11) << endl;
    cout << "elemento 20: " << quickSelect(vector, 0, 21, 20) << endl;
    printList(vector, 21);

    cout << endl << "Median of Medians Select" << endl;
    float vector2[] = {10.9, -2.3, 3, 6.12, 78, -9, 4, 3, -14, 39, 3, 1, 5.45, 12, -19,4, 0, -1, 1, 9, 12.9}; //21 elements
    printList(vector2, 21);
    cout << "elemento 0: " << MOMSelect(vector2, 0, 21, 0) << endl;
    cout << "elemento 11: " << MOMSelect(vector2, 0, 21, 11) << endl;
    cout << "elemento 20: " << MOMSelect(vector2, 0, 21, 20) << endl;
    printList(vector2, 21);
}*/
