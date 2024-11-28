#ifndef GraphsH
#define GraphsH

typedef int vertex;

struct EdgeNode {
    vertex vert;
    EdgeNode* next;
    int weight;
};


//Space complexity to store the graph: theta(len(V)^2)
class GraphMatrix {
private:
    int m_numVertex; //Immutable
    int m_numEdges; //Edges count will be track to easen life in some parts
    int** m_edges; //Two references because it's a matrix

public:
    GraphMatrix(int);
    ~GraphMatrix();
    int** edges();

    bool hasEdge(vertex, vertex); //theta(1) - constant, only acess value in array
    void addEdge(vertex, vertex, int = 1); //theta(1)
    void removeEdge(vertex, vertex); //theta(1)
    void addEdgesFromTree(vertex[]);

    void print(); //theta(V^2)
    void printMatrix(); //theta(V^2)

    bool isSubGraph(GraphMatrix&); //theta(V^2)
    bool isValidPath(vertex[], int, bool&); //theta(n)

    //Graph search algorithms

    bool hasPath(vertex, vertex); //theta(V^2) - envelops below function
    void findConnected(vertex, bool[]); //theta(V^2)
    void dfs(int[], int[], vertex[]); //theta(V^2) - same idea of the above algorithms, but now saving lots of information
    void dfsRecursive(vertex, int[], int&, int[], int&, vertex[]);

    bool isTopological(); //theta(V^2)
    bool hasTopologicalOrder(int[]); //theta(V^2)

    void bfsForest(int[]); //theta(V^2)
    void bfsTree(vertex, int[], vertex[]); //O(V^2)

    //Graph minimal path algorithms

    void dagSPT(vertex[], int[]); //theta(V^2)
    void SPT(vertex, vertex[], int[], int = -1); //O(V^2)
    void CPTDijkstra(vertex, vertex[], int[]); //O((V^2)log(V))
    bool CPTBellmanFord(vertex, vertex[], int[]); //theta(V^3)

    //MST algorithms

    void slowPrim(vertex[], vertex = 0);
    void slowKruskal(vertex[], vertex[]);
};


class GraphAdjList {
private:
    int m_numVertex; //Immutable
    int m_numEdges; //Edges count will be track to easen life in some parts
    EdgeNode** m_edges; //Two references because it's a list of nodes

public:
    GraphAdjList(int);
    ~GraphAdjList();
    EdgeNode** edges();

    bool hasEdge(vertex, vertex); //O(V)
    void addEdge(vertex, vertex, int = 1); //O(V)
    void removeEdge(vertex, vertex); //O(V)
    void addEdgesFromTree(vertex[]);

    void print(); //O(V + E)

    bool isSubGraph(GraphAdjList&); //O(E + E')
    bool isValidPath(vertex[], int, bool&); //O(n * V)

    //Graph search algorithms

    bool hasPath(vertex, vertex); //O(V + E) - envelops below function
    void findConnected(vertex, bool[]); //O(V + E)
    void dfs(int[], int[], vertex[]); //O(V + E) - same idea of the above algorithms, but now saving lots of information
    void dfsRecursive(vertex, int[], int&, int[], int&, vertex[]); //O(V + E)

    bool isTopological(); //theta(V + E)
    bool hasTopologicalOrder(int[]); //theta(V + E)

    void bfsForest(int[]); //theta(V + E)
    void bfsTree(vertex, int[], vertex[]); //O(V + E)

    //Graph minimal path algorithms

    void dagSPT(vertex[], int[]); //theta(V + E)
    void SPT(vertex, vertex[], int[], int = -1); //O(V + E)
    void CPTDijkstra(vertex, vertex[], int[]); //O((V + E)log(V))
    bool CPTBellmanFord(vertex, vertex[], int[]); //O(VE)

    //MST algorithms

    void slowPrim(vertex[], vertex = 0); //O(V^3)
    void slowKruskal(vertex[], vertex[]);
    void kruskal(vertex[], vertex[]);
};

#endif
