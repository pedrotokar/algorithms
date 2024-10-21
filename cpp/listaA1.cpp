#include <iostream>
#include "sorting.h"
#include "selection.h"
#include <structs/Heaps.h>
#include <structs/Trees.h>
#include <structs/HashTables.h>
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << "]" << endl;}
#define displayKey(table, k) {if (table->get(k) == nullptr) {cout << "Não há chave " << k << endl;} else {cout << k << ": " <<  table->get(k)->value << endl;};}

using namespace std;


template <typename T> //aux function for exercises
T dist(T x1, T x2){
    T result = x1 - x2;
    if (result < 0){
        result = result * -1;
    }
    return result;
}

//Define Median of Medians select algorithm but with comparisons made with hashtables ------------------------------------

template <typename T>
int partitionate(T vector[], int iStart, int iEnd, HashTable<int>* H){
    int iLast = iEnd - 1;
    int j = iStart;
    for (int i = iStart; i < iLast; i++){
        if (H->get(vector[i])->value <= H->get(vector[iLast])->value){
            swap(vector, i, j);
            j++;
        }
    }
    swap(vector, j, iLast);
    return j;
}

template <typename T>
int partitionateByElement(T vector[], int iStart, int iEnd, T iPartition, HashTable<int>* H){
    int j = -1;
    for (int i = iStart; i < iEnd; i++){
        if (vector[i] == iPartition){
            j = i;
            break;
        }
    }
    if(j == -1) return -1;
    swap(vector, j, iEnd - 1);
    return partitionate(vector, iStart, iEnd, H); //returns element new index
}

template <typename T>
void quickSort(T vector[], int iStart, int iEnd, HashTable<int>* H){
    while (iStart < iEnd - 1){
        int iMid = partitionate(vector, iStart, iEnd, H); //This function, in pratical use, is different and tries to always partitionate closer to the half of the array
        if (iMid - iStart < iEnd - iMid) { //Computing the shortest first, then goes back and computes the greater (withouth needing to call the function two times)
            quickSort(vector, iStart, iMid, H);
            iStart = iMid;
        } else {
            quickSort(vector, iMid, iEnd, H);
            iEnd = iMid;
        }
    }
}

template <typename T>
T findMedian(T vector[], int iStart, int iEnd, HashTable<int>* H){
    quickSort(vector, iStart, iEnd, H);
    return vector[iStart + (iEnd - iStart)/2];
}

template <typename T>
T MOMSelect(T vector[], int iStart, int iEnd, int iSearch, HashTable<int>* H){
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
        medians[i] = findMedian(vector, iStart + i * 5, iStart + (i + 1) * 5, H);
    }
    medians[i] = findMedian(vector, iStart + i * 5, iEnd, H);
    T MOM;
    if (i == 0){
        MOM = medians[0];
    } else {
        MOM = MOMSelect(medians, 0, i, i/2, H);
    }
    int iPivot = partitionateByElement(vector, iStart, iEnd, MOM, H);
    if (iPivot == iSearch){
        return vector[iPivot];
    } else if (iPivot < iSearch){
        return MOMSelect(vector, iPivot + 1, iEnd, iSearch, H);
    } else {
        return MOMSelect(vector, iStart, iPivot, iSearch, H);
    }
}

//Define Median of Medians select algorithm but with comparisons made with distance to a number --------------------------

template <typename T>
int partitionate(T vector[], int iStart, int iEnd, T x){
    int iLast = iEnd - 1;
    int j = iStart;
    for (int i = iStart; i < iLast; i++){
        if (dist(vector[i], x) <= dist(vector[iLast], x)){
            swap(vector, i, j);
            j++;
        }
    }
    swap(vector, j, iLast);
    return j;
}

template <typename T>
int partitionateByElement(T vector[], int iStart, int iEnd, T iPartition, T x){
    int j = -1;
    for (int i = iStart; i < iEnd; i++){
        if (vector[i] == iPartition){
            j = i;
            break;
        }
    }
    if(j == -1) return -1;
    swap(vector, j, iEnd - 1);
    return partitionate(vector, iStart, iEnd, x); //returns element new index
}

template <typename T>
void quickSort(T vector[], int iStart, int iEnd, T x){
    while (iStart < iEnd - 1){
        int iMid = partitionate(vector, iStart, iEnd, x); //This function, in pratical use, is different and tries to always partitionate closer to the half of the array
        if (iMid - iStart < iEnd - iMid) { //Computing the shortest first, then goes back and computes the greater (withouth needing to call the function two times)
            quickSort(vector, iStart, iMid, x);
            iStart = iMid;
        } else {
            quickSort(vector, iMid, iEnd, x);
            iEnd = iMid;
        }
    }
}

template <typename T>
T findMedian(T vector[], int iStart, int iEnd, T x){
    quickSort(vector, iStart, iEnd, x);
    return vector[iStart + (iEnd - iStart)/2];
}

template <typename T>
T MOMSelect(T vector[], int iStart, int iEnd, int iSearch, T x){
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
        medians[i] = findMedian(vector, iStart + i * 5, iStart + (i + 1) * 5, x);
    }
    medians[i] = findMedian(vector, iStart + i * 5, iEnd, x);
    T MOM;
    if (i == 0){
        MOM = medians[0];
    } else {
        MOM = MOMSelect(medians, 0, i, i/2, x);
    }
    int iPivot = partitionateByElement(vector, iStart, iEnd, MOM, x);
    if (iPivot == iSearch){
        return vector[iPivot];
    } else if (iPivot < iSearch){
        return MOMSelect(vector, iPivot + 1, iEnd, iSearch, x);
    } else {
        return MOMSelect(vector, iStart, iPivot, iSearch, x);
    }
}

//Define Merge Sort algorithm but with comarisons made with distance to a number -----------------------------------------

template <typename T>
void mergeArrays(T vector[], int iStart, int iEnd, T x){
    int iMid = iStart + (iEnd - iStart)/2;
    T vector2[iEnd - iStart];
    int iPosLeft = iStart;
    int iPosRight = iMid;
    int iPosNew = 0;
    while (iPosLeft < iMid && iPosRight < iEnd){
        if(dist(vector[iPosLeft], x) <= dist(vector[iPosRight], x)){
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

template <typename T>
void mergeSort(T vector[], int iStart, int iEnd, T x){
    if (iStart < iEnd - 1){
        int iMid = iStart + (iEnd - iStart)/2;
        mergeSort(vector, iStart, iMid, x);
        mergeSort(vector, iMid, iEnd, x);
        mergeArrays(vector, iStart, iEnd, x);
    }
}

//Finally after two hundred lines, the list solutions.

int ex7(int vector[], int iLength, int k){
    int integers[iLength];
    int m = 0;
    HashTable<int>* freqs = new HashTable<int>(iLength);
    for (int i = 0; i <iLength; i++){
        if(freqs->get(vector[i]) == nullptr){
            integers[m] = vector[i];
            m++;
            freqs->set(vector[i], 1);
        } else {
            freqs->set(vector[i], freqs->get(vector[i])->value + 1);
        }
    }
    int x = MOMSelect(integers, 0, m, m - k, freqs);
    return x;
}

bool ex8(int vector[], int iLength, int x, int result[]){
    HashTable<int>* appears = new HashTable<int>(iLength);
    for (int i = 0; i < iLength; i++){
        if (appears->get(vector[i]) == nullptr){
            appears->set(vector[i], 1);
        }
    }
    for (int i = 0; i < iLength; i++){
        if (appears->get(x - vector[i]) != nullptr){
            result[0] = vector[i];
            result[1] = x - vector[i];
            return true;
        }
    }
    return false;
}

int ex9(int vector[], int iCount, int iLength){
    int iDisjuncts = 0;
    HashTable<int>* freqs = new HashTable<int>(iLength * iCount);
    for (int i = 0; i < iCount; i++){
        for (int j = 0; j < iLength; j++){
            if(freqs->get(vector[i*iCount + i + j]) == nullptr){
                freqs->set(vector[i*iCount + i + j], 1);
            } else {
                freqs->set(vector[i*iCount + i + j], freqs->get(vector[i*iCount + i + j])->value + 1);
            }
        }
    }
    for (int i = 0; i < iCount; i++){
        bool bIntersects = false;
        HashTable<int>* aux = new HashTable<int>(iLength);

        for (int j = 0; j < iLength; j++){
            if(aux->get(vector[i*iCount + i + j]) == nullptr){
                aux->set(vector[i*iCount + i + j], 1);
            } else {
                aux->set(vector[i*iCount + i + j], aux->get(vector[i*iCount + i + j])->value + 1);
            }
        }

        for (int j = 0; j < iLength; j++){
            if(aux->get(vector[i*iCount + i + j])->value < freqs->get(vector[i*iCount + i + j])->value){
                bIntersects = true;
                break;
            }
        }
        if(not bIntersects){
            iDisjuncts++;
        }
        delete aux;
    }
    return iDisjuncts;
}


int ex10(int vector[], int iStart, int iEnd, int iRealEnd){
    if (iStart == iEnd - 1){
        if ((iRealEnd - iStart) >= vector[iStart]){
            return vector[iStart];
        } else {
            return -1;
        }
    }
    int iMedian = MOMSelect(vector, iStart, iEnd, iStart + (iEnd - iStart)/2);
    int iPivot = partitionateByElement(vector, iStart, iEnd, iMedian);
    if ((iRealEnd - iPivot) >= iMedian){
        int iCompare = ex10(vector, iPivot + 1, iEnd, iRealEnd);
        return max(iCompare, iMedian);
    } else {
        int iCompare = ex10(vector, iStart, iPivot, iRealEnd);
        return max(iCompare, -1);
    }
}

int ex11(NodeTree<int>* ptrRoot, int iSize){
    int vector[iSize];
    dfsFlatten(vector, ptrRoot, 0);
    //printList(vector, iSize);
    int minDistance = 2147483647; //inf
    for(int i = 1; i < iSize; i++){
        if (vector[i] - vector[i - 1] <= minDistance){
            minDistance = vector[i] - vector[i - 1];
        }
    }
    return minDistance;
}

void ex12(int vector[], int iLength, int x, int k, int result[]){
    if (k >= iLength) return;
    int kesimodistante = MOMSelect(vector, 0, iLength, k, x);
    partitionateByElement(vector, 0, iLength - 1, kesimodistante, x);
    mergeSort(vector, 0, k, x);
    for (int i = 0; i < k; i++){
        result[i] = vector[i];
    }
}

int ex13(int vector[], int iLength, int x, int result[]){
    heapSort(vector, iLength);
    int bestPair[2] = {0, 0}; //i inclusive, j exclusive
    int i = 0;
    int j = 1; //starts with only sublist [0]
    for(int j = 1; j <= iLength; j++){
        while(vector[j - 1] - vector[i] > x && j > i){
            i++;
        }
        if(j - i >= bestPair[1] - bestPair[0]){
            bestPair[1] = j;
            bestPair[0] = i;
        }
    }
    for (int i = bestPair[0]; i < bestPair[1]; i++){
        result[i - bestPair[0]] = vector[i];
    }
    return (bestPair[1] - bestPair[0] > 1) ? bestPair[1] - bestPair[0] : 0;
}

void ex14(int vector[], int iLength, int result[]){
    int i = 0;
    int j = iLength - 1;
    int maxValue = -2147483647; //-inf
    while (i < j){
        if ((dist(i, j) * min(vector[i], vector[j]) >= maxValue)) {
            maxValue = (dist(i, j) * min(vector[i], vector[j]));
            result[0] = i;
            result[1] = j;
        }
        if (vector[i] <= vector[j]) {
            i++;
        } else {
            j--;
        }
    }
}

NodeTree<int>* ex15(int vector[], int iStart, int iEnd){
    int iLength = iEnd - iStart;
    if (iLength == 1){
        return newNodeTree(vector[iStart]);
    }
    else if (iLength == 2){
        NodeTree<int>* parentNode = newNodeTree(max(vector[iStart], vector[iStart + 1]));
        parentNode->ptrLeft = newNodeTree(min(vector[iStart], vector[iStart + 1]));
        return parentNode;
    }
    int iMedian = MOMSelect(vector, iStart, iEnd, iStart + iLength/2);
    int iPivot = partitionateByElement(vector, iStart, iEnd, iMedian);
    NodeTree<int>* parentNode = newNodeTree(vector[iPivot]);
    parentNode->ptrLeft = ex15(vector, iStart, iPivot);
    parentNode->ptrRight = ex15(vector, iPivot + 1, iEnd);
    return parentNode;
}

int main(){

    cout << "Exercício 7" << endl;
    int vector_7[] = {20, 30, 40, -1, 30, 30, 30, 20, 20, -1, 20, 20, 10, 10, 10, 10}; //16 elementos
    printList(vector_7, 16);
    cout << ex7(vector_7, 16, 1) << endl;

    cout << endl << "Exercício 8" << endl;
    int vector_8[] = {10, 2, 13, 6, 78, -9, 4, 30, 14, 39, 31, 1, 5, 12}; //14 elementos
    int resultado8[2] = {0, 0};
    printList(vector_8, 14);
    cout << ex8(vector_8, 14, 19, resultado8) << " ";
    printList(resultado8, 2);

    cout << endl << "Exercício 9" << endl;
    int vector_9[] = {13, 2, 14, 6, 78,
                      -9, 4, 3, 14, 39,
                      3, 1, 5, 12, 4,
                      -1, 79, 80, 81, 90}; //20 elementos (4 subarrays de 5 elementos)
    cout << ex9(vector_9, 4, 5) << endl;

    cout << endl << "Exercício 10" << endl;
    int vector_10[] = {1, 20, 21, 1, 3 , 2}; // 6 elementos
    printList(vector_10, 6);
    cout << ex10(vector_10, 0, 6, 6) << endl;

    cout << endl << "Exercício 12" << endl;
    int vector_12[] = {1, 2, 7, 3, 9, 8, 4, 6, 5, 10}; //10 elementos
    printList(vector_12, 10);
    int k = 5;
    int resultado12[k];
    ex12(vector_12, 10, 5, k, resultado12);
    printList(resultado12, k);

    cout << endl << "Exercício 13" << endl;
    int vector_13[] = {10, 2, 13, 6, 78, -9, 4, 30, 14, 39, 31, 1, 5, 12}; //14 elementos
    printList(vector_13, 14);
    int resultado13[14];
    int size = ex13(vector_13, 14, 2, resultado13);
    printList(resultado13, size);

    cout << endl << "Exercício 14" << endl;
    int vector_14[] = {2, 7, -5, 3, -4, 6};
    printList(vector_14, 6);
    int resultado14[2];
    ex14(vector_14, 6, resultado14);
    printList(resultado14, 2);

    cout << endl << "Exercícios 15 e 11" << endl;
    int vector_15[] = {-10, 6, 78, 9, 14, 39, 1, 50, 12, 34, -2, -13, 98, 48, 17, 21, 85, 23}; //20 elementos
    printList(vector_15, 18);
    NodeTree<int>* tree = ex15(vector_15, 0, 18);
    dfsTraverseInOrder(tree);
    cout << endl;
    //dfsTraversePostOrder(tree);
    //cout << endl;
    //dfsTraversePreOrder(tree);
    //cout << endl;
    //bfsTraverse(tree);
    //cout << endl;
    cout << ex11(tree, 18) << endl;

    //printList(vector_1, 14);
    //printList(vector_3, 27);
    //printList(vector_4, 6);
    //printList(vector_5, 16);
    //printList(vector_6, 10);
    //printList(vector_7, 6);
}
