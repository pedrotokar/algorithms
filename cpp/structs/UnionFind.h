#ifndef UnionFindH
#define UnionFindH

typedef int element;

class UnionFind {
private:
    element m_numElements; //Immutable
    element* m_group; //Edges count will be track to easen life in some parts
    int* m_groupSize; //Two references because it's a matrix

public:
    UnionFind(int);
    ~UnionFind();

    element findE(element); //O(log(n))
    void unionE(element, element); //O(1)
};

#endif
