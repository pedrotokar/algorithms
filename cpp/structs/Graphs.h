#ifndef GraphsH
#define GraphsH

typedef int vertex;

struct EdgeNode {
    vertex vert;
    EdgeNode* next;
};


//Space complexity to store the graph: theta(len(V)^2)
class GraphMatrix {
private:
    int m_numVertices; //Immutable
    int m_numEdges; //Edges count will be track to easen life in some parts
    int** m_edges; //Two references because it's a matrix

public:
    GraphMatrix(int numVertices);
    ~GraphMatrix();
    int** edges();

    bool hasEdge(vertex, vertex); //theta(1) - constant, only acess value in array
    void addEdge(vertex, vertex); //theta(1)
    void removeEdge(vertex, vertex); //theta(1)

    void print(); //theta(V^2)
    void printMatrix(); //theta(V^2)

    bool isSubGraph(GraphMatrix&); //theta(V^2)
    bool isValidPath(vertex[], int, bool&); //theta(n)

    bool hasPath(vertex, vertex); //theta(V^2) - envelops below function
    void findConnected(vertex, bool[]); //theta(V^2)
    void dfs(int[], int[], int[]);
    void dfsRecursive(vertex, int[], int&, int[], int&, int[]);

    bool isTopological(); //theta(V^2)
    bool hasTopologicalOrder(int[]); //theta(V^2)
};


class GraphAdjList {
private:
    int m_numVertices; //Immutable
    int m_numEdges; //Edges count will be track to easen life in some parts
    EdgeNode** m_edges; //Two references because it's a list of nodes

public:
    GraphAdjList(int numVertices);
    ~GraphAdjList();
    EdgeNode** edges();

    bool hasEdge(vertex, vertex); //O(V)
    void addEdge(vertex, vertex); //O(V)
    void removeEdge(vertex, vertex); //O(V)

    void print(); //O(V + E)

    bool isSubGraph(GraphAdjList&); //O(E + E')
    bool isValidPath(vertex[], int, bool&); //O(n * V)

    bool hasPath(vertex, vertex); //O(V + E) - envelops below function
    void findConnected(vertex, bool[]); //O(V + E)
    void dfs(int[], int[], int[]);
    void dfsRecursive(vertex, int[], int&, int[], int&, int[]);

    bool isTopological(); //theta(V + E)
    bool hasTopologicalOrder(int[]); //theta(V + E)
};

#endif
