#include <iostream>
#include "Trees.h"

using namespace std;

//Functions to manipulate trees
template <typename T> NodeTree<T>* newNodeTree(T);
template <typename T> NodeTree<T>* insertNodeTree(NodeTree<T>*, T);
template <typename T> NodeTree<T>* lesserLeaf(NodeTree<T>*);
template <typename T> NodeTree<T>* deleteNodeTree(NodeTree<T>*, T);
template <typename T> int treeHeight(NodeTree<T>*);
NodeTree<int> *createRandomTree(int, int, int, int);
template <typename T> void freeTree(NodeTree<T>*);

//Search algorithms
template <typename T> NodeTree<T>* dfsSearchNode(NodeTree<T>*, T);
template <typename T> NodeTree<T>* bfsSearchNode(NodeTree<T>*, T);

//Traverse Algorithms
template <typename T> void dfsTraversePreOrder(NodeTree<T>*);
template <typename T> void dfsTraverseInOrder(NodeTree<T>*);
template <typename T> void dfsTraversePostOrder(NodeTree<T>*);
template <typename T> int dfsFlatten(T[], NodeTree<T>*, int);

template <typename T> void bfsTraverse(NodeTree<T>*);

//Queue structure to help in traversing algorithms
template <typename T>
struct NodeQueue
{
    NodeTree<T>* ptrPayload;
    NodeQueue* ptrNext;
};

template <typename T> void insertEndQueue(NodeQueue<T>**, NodeTree<T>*); //Help function to manipulate the queue

template <typename T>
void insertEndQueue(NodeQueue<T>** head, NodeTree<T>* ptrPayload){
    NodeQueue<T>* newNode = (NodeQueue<T>*) malloc(sizeof(NodeQueue<T>));
    newNode->ptrPayload = ptrPayload;
    newNode->ptrNext = nullptr;

    if (*head == nullptr){
        (*head) = newNode;
        return;
    }

    NodeQueue<T>* current = (*head);
    while (current->ptrNext != nullptr) current = current->ptrNext;

    current->ptrNext = newNode;

    return;
}

template <typename T>
NodeTree<T>* newNodeTree(T iData){
    NodeTree<T>* tmp = (NodeTree<T>*) malloc(sizeof(NodeTree<T>));
  
    if (tmp != nullptr){
        tmp->iPayload = iData;
        tmp->ptrLeft = nullptr;
        tmp->ptrRight = nullptr;
    }
  
    return tmp;
}

template <typename T>
NodeTree<T>* insertNodeTree(NodeTree<T>* startingNode, T iData)
{
    if(startingNode == nullptr){
        return newNodeTree(iData);
    }
    
    if(iData < startingNode->iPayload){
        startingNode->ptrLeft = insertNodeTree(startingNode->ptrLeft, iData);
    }
    else{
        startingNode->ptrRight = insertNodeTree(startingNode->ptrRight, iData);
    }
    
    return startingNode;
}

NodeTree<int> *createRandomTree(int iBottomLimit, int iTopLimit, int iQuantity, int iSeed){
    NodeTree<int> *head = nullptr;
    srand(iSeed);
    for (int i = 0; i < iQuantity; i++){
        head = insertNodeTree(head, iBottomLimit + (rand() % (iTopLimit - iBottomLimit)));
    }
    return head;
}

template <typename T>
NodeTree<T>* dfsSearchNode(NodeTree<T>* startingNode, T iData){
    if(startingNode == nullptr) return nullptr;
    else if(iData == startingNode->iPayload) return startingNode;
    else if(iData < startingNode->iPayload) return dfsSearchNode(startingNode->ptrLeft, iData);
    else return dfsSearchNode(startingNode->ptrRight, iData);
}

template <typename T>
NodeTree<T>* lesserLeaf(NodeTree<T>* startingNode){
    NodeTree<T>* ptrCurrent = startingNode;
 
    while (ptrCurrent && ptrCurrent->ptrLeft != nullptr) ptrCurrent = ptrCurrent->ptrLeft;
    
    return ptrCurrent;
}

template <typename T>
NodeTree<T>* deleteNodeTree(NodeTree<T>* startingNode, T iData){
    if (startingNode == nullptr) return nullptr;
    
    if (iData < startingNode->iPayload) startingNode->ptrLeft = deleteNodeTree(startingNode->ptrLeft, iData);
    else if (iData > startingNode->iPayload) startingNode->ptrRight = deleteNodeTree(startingNode->ptrRight, iData);
    else{
        NodeTree<T>* ptrTemp = nullptr;
        
        if (startingNode->ptrLeft == nullptr){
            ptrTemp = startingNode->ptrRight;
            free(startingNode);
            return ptrTemp;
        }
        else if (startingNode->ptrRight == nullptr){
            ptrTemp = startingNode->ptrLeft;
            free(startingNode);
            return ptrTemp;            
        }
        
        ptrTemp = lesserLeaf(startingNode->ptrRight);
        
        startingNode->iPayload = ptrTemp->iPayload;
        
        startingNode->ptrRight = deleteNodeTree(startingNode->ptrRight, ptrTemp->iPayload);
    }
    
    return startingNode;
}

template <typename T>
void dfsTraversePreOrder(NodeTree<T>* ptrStartingNode){
    if (ptrStartingNode != nullptr){
        cout << " " << ptrStartingNode->iPayload;
        dfsTraversePreOrder(ptrStartingNode->ptrLeft);
        dfsTraversePreOrder(ptrStartingNode->ptrRight);
    }
}

template <typename T>
void dfsTraverseInOrder(NodeTree<T>* ptrStartingNode){
    if (ptrStartingNode != nullptr){
        dfsTraverseInOrder(ptrStartingNode->ptrLeft);
        cout << " " << ptrStartingNode->iPayload;
        dfsTraverseInOrder(ptrStartingNode->ptrRight);
    }
}

template <typename T>
void dfsTraversePostOrder(NodeTree<T>* ptrStartingNode){
    if (ptrStartingNode != nullptr){
        dfsTraversePostOrder(ptrStartingNode->ptrLeft);
        dfsTraversePostOrder(ptrStartingNode->ptrRight);
        cout << " " << ptrStartingNode->iPayload;
    }
}

template <typename T>
int dfsFlatten(T vector[], NodeTree<T>* ptrStartingNode, int iIndex){
    if (ptrStartingNode != nullptr){
        iIndex = dfsFlatten(vector, ptrStartingNode->ptrLeft, iIndex);
        vector[iIndex] = ptrStartingNode->iPayload;
        iIndex++;
        iIndex = dfsFlatten(vector, ptrStartingNode->ptrRight, iIndex);
    }
    return iIndex;
}

template <typename T>
void bfsTraverse(NodeTree<T>* startingNode){
    if (startingNode == nullptr) return;
    
    NodeQueue<T>* ptrQueue = nullptr;
    insertEndQueue(&ptrQueue, startingNode);
    
    while (ptrQueue != nullptr){
        NodeTree<T>* currentNode = ptrQueue->ptrPayload;
        ptrQueue = ptrQueue->ptrNext;
        
        cout << currentNode->iPayload << " ";
    
        if (currentNode->ptrLeft != nullptr){
            insertEndQueue(&ptrQueue, currentNode->ptrLeft);
        }
        
        if (currentNode->ptrRight != nullptr){
            insertEndQueue(&ptrQueue, currentNode->ptrRight);
        }
    }
}

template <typename T>
NodeTree<T>* bfsSearchNode(NodeTree<T>* root, T iPayload){
    if (root == nullptr) return nullptr;

    NodeQueue<T>* ptrQueue = nullptr;
    insertEndQueue(&ptrQueue, root);
    
    while (ptrQueue != nullptr){
        NodeTree<T>* currentNode = ptrQueue->ptrPayload;
        ptrQueue = ptrQueue->ptrNext;
        
        if (currentNode->iPayload == iPayload) return currentNode;  
    
        if (currentNode->ptrLeft != nullptr){
            insertEndQueue(&ptrQueue, currentNode->ptrLeft);
        }
        
        if (currentNode->ptrRight != nullptr){
            insertEndQueue(&ptrQueue, currentNode->ptrRight);
        }
    }
    return nullptr;
}

template <typename T>
int treeHeight(NodeTree<T>* startingNode){
    if (startingNode == nullptr) return 0;
    else{
        int iLeftHeight = treeHeight(startingNode->ptrLeft);
        int iRightHeight = treeHeight(startingNode->ptrRight);
        
        return max(iLeftHeight, iRightHeight) + 1;
    }
}

template <typename T>
void freeTree(NodeTree<T>* ptrStartingNode){
    if (ptrStartingNode != nullptr){
        freeTree(ptrStartingNode->ptrLeft);
        freeTree(ptrStartingNode->ptrRight);
        free(ptrStartingNode);
    }
}

template NodeTree<int>* newNodeTree(int);
template NodeTree<int>* insertNodeTree(NodeTree<int>*, int);
template NodeTree<int>* lesserLeaf(NodeTree<int>*);
template NodeTree<int>* deleteNodeTree(NodeTree<int>*, int);
template int treeHeight(NodeTree<int>*);
template NodeTree<int>* dfsSearchNode(NodeTree<int>*, int);
template NodeTree<int>* bfsSearchNode(NodeTree<int>*, int);
template void dfsTraversePreOrder(NodeTree<int>*);
template void dfsTraverseInOrder(NodeTree<int>*);
template void dfsTraversePostOrder(NodeTree<int>*);
template int dfsFlatten(int[], NodeTree<int>*, int);
template void bfsTraverse(NodeTree<int>*);
template void freeTree(NodeTree<int>*);
