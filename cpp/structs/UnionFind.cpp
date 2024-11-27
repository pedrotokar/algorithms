#include <iostream>
#include "UnionFind.h"
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << "]" << endl;}

using namespace std;

UnionFind::UnionFind(int numElements):
m_numElements(numElements), m_group(nullptr), m_groupSize(nullptr){
    m_group = new element[m_numElements];
    m_groupSize = new int[m_numElements];
    for(int i = 0; i <m_numElements; i++){
        m_group[i] = i;
        m_groupSize[i] = 1;
    }
}

UnionFind::~UnionFind(){
    delete m_group;
    delete m_groupSize;
}

//O(log(n))
element UnionFind::findE(element e){
    element leader = e;
    while(leader != m_group[leader]){
        leader = m_group[leader];
    }
    return leader;
}

//O(1)
void UnionFind::unionE(element e1, element e2){
    if (m_groupSize[e1] > m_groupSize[e2]){
        m_groupSize[e1] += m_groupSize[e2];
        m_group[e2] = e1;
    }
    else{
        m_groupSize[e2] += m_groupSize[e1];
        m_group[e1] = e2;
    }
}
