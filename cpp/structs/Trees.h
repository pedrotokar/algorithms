#ifndef TreesH
#define TreesH

template <typename T>
struct NodeTree
{
    T iPayload;
    NodeTree* ptrLeft;
    NodeTree* ptrRight;

};

template struct NodeTree<int>;

template <typename T> NodeTree<T>* newNodeTree(T);
template <typename T> NodeTree<T>* insertNodeTree(NodeTree<T>*, T);
template <typename T> NodeTree<T>* lesserLeaf(NodeTree<T>*);
template <typename T> NodeTree<T>* deleteNodeTree(NodeTree<T>*, T);
template <typename T> int treeHeight(NodeTree<T>*);
template <typename T> NodeTree<T>* dfsSearchNode(NodeTree<T>*, T);
template <typename T> NodeTree<T>* bfsSearchNode(NodeTree<T>*, T);
template <typename T> void dfsTraversePreOrder(NodeTree<T>*);
template <typename T> void dfsTraverseInOrder(NodeTree<T>*);
template <typename T> void dfsTraversePostOrder(NodeTree<T>*);
template <typename T> void bfsTraverse(NodeTree<T>*);
template <typename T> int dfsFlatten(T[], NodeTree<T>*, int);
NodeTree<int> *createRandomTree(int, int, int, int);
template <typename T> void freeTree(NodeTree<T>*);

#endif
