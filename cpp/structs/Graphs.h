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

    void print();
    void printMatrix();

    bool isSubGraph(GraphMatrix&);
    bool isValidPath(vertex[], int);
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

    void addEdge(vertex, vertex);
    void removeEdge(vertex, vertex);

    void print();

    bool isSubGraph(GraphAdjList&);
    bool isValidPath(vertex[], int);
};

#endif
