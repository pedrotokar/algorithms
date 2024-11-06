#include <iostream>
#include "Graphs.h"
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << " ]" << endl;}

using namespace std;

//Space complexity to store the graph: theta(len(V)^2)
GraphMatrix::GraphMatrix(int numVertices):
m_numVertices(numVertices), m_numEdges(0), m_edges(nullptr){ //Already initializes the graph attributes
    m_edges = new int*[numVertices]; //new array of arrays of ints
    for (vertex i = 0; i < m_numVertices; i++){
        m_edges[i] = new int[numVertices];
        for (vertex j = 0; j <m_numVertices; j++){
            m_edges[i][j] = 0; //fill everything with zeros
        }
    }
}

GraphMatrix::~GraphMatrix(){
    for (vertex i = 0; i < m_numVertices; i++){
        delete[] m_edges[i];
    }
    delete[] m_edges;
}

int** GraphMatrix::edges() {return m_edges;}

//theta(1) - constant, only acess value in array
bool GraphMatrix::hasEdge(vertex v1, vertex v2){
    if(v1 >= 0 && v1 < m_numVertices && v2 >= 0 && v2 <m_numVertices){
        if(m_edges[v1][v2] > 0){
            return true;
        }
    }
    return false;
}

//theta(1)
void GraphMatrix::addEdge(vertex v1, vertex v2){
    if(v1 >= 0 && v1 < m_numVertices && v2 >= 0 && v2 <m_numVertices){
        if (!hasEdge(v1, v2)){
            m_numEdges++;
            m_edges[v1][v2] = 1;
        }
    }
}

//theta(1)
void GraphMatrix::removeEdge(vertex v1, vertex v2){
    if(v1 >= 0 && v1 < m_numVertices && v2 >= 0 && v2 <m_numVertices){
        if (hasEdge(v1, v2)){
            m_numEdges--;
            m_edges[v1][v2] = 0;
        }
    }
}

//theta(V^2)
void GraphMatrix::print(){
    cout << m_numEdges << " [ ";
    for (vertex i = 0; i < m_numVertices; i++){
        for (vertex j = 0; j <m_numVertices; j++){
            if (hasEdge(i, j)){
                cout << "(" << i << " " << j << " " << m_edges[i][j] << ") ";
            }
        }
        //cout << endl;
    }
    cout << "]" << endl;
}

//theta(V^2)
void GraphMatrix::printMatrix(){
    for (vertex i = 0; i < m_numVertices; i++){
        for (vertex j = 0; j <m_numVertices; j++){
            cout << m_edges[i][j] << " ";
        }
        cout << endl;
    }
}

//theta(V^2)
bool GraphMatrix::isSubGraph(GraphMatrix& H) {
    int** hEdges = H.edges();
    for (vertex i = 0; i < m_numVertices; i++){
        for (vertex j = 0; j <m_numVertices; j++){
            if(hEdges[i][j] > 0){
                if(!hasEdge(i, j)){
                    return false;
                }
            }
        }
    }
    return true;
}

//theta(n)
bool GraphMatrix::isValidPath(vertex path[], int iLength, bool& hasCycle){
    if (iLength < 2) return false;
    bool visited[m_numVertices];
    for (vertex i = 0; i <m_numVertices; i++) {visited[i] = false;}
    visited[path[0]] = true;
    for(int i = 1; i < iLength; i++){
        if(visited[path[i]]) hasCycle = true;
        if(!hasEdge(path[i-1],path[i])){
            return false;
        }
        visited[path[i]] = true;
    }
    return true;
}

//Implements everything but now for adjacency list graphs-------------------------------------------------------

GraphAdjList::GraphAdjList(int numVertices):
m_numVertices(numVertices), m_numEdges(0), m_edges(nullptr){
    m_edges = new EdgeNode*[numVertices]; //Initializes the list of edges for each vetex
    for (vertex i = 0; i < numVertices; i++) {
        m_edges[i] = nullptr; //No edges exist yet
    }
}

GraphAdjList::~GraphAdjList(){
    for (vertex i = 0; i < m_numVertices; i++){
        EdgeNode* node = m_edges[i]; //Get the list head of edges for that vertex
        while (node != nullptr) { //And goes deleting everything
            EdgeNode* nextNode = node->next;
            delete node;
            node = nextNode;
        }
    }
    delete[] m_edges;
}

EdgeNode** GraphAdjList::edges() {return m_edges;}

//O(V)
bool GraphAdjList::hasEdge(vertex v1, vertex v2){
    EdgeNode* node = m_edges[v1];
    while(node){
        if(node->vert == v2){
            return true;
        }
        node = node->next;
    }
    return false;
}

//O(V) because in worst case it adds on the end of the list
void GraphAdjList::addEdge(vertex v1, vertex v2){
    if(v1 >= 0 && v1 < m_numVertices && v2 >= 0 && v2 <m_numVertices){
        EdgeNode* node = m_edges[v1]; //Get the list head of edges for that vertex
        if(node == nullptr || node->vert >= v2){
            m_edges[v1] = new EdgeNode;
            m_edges[v1]->next = node;
            m_edges[v1]->vert = v2;
            m_numEdges++;
        } else{
            while(node->next != nullptr && node->next->vert < v2) {
                node = node->next;
            }
            if(node->next == nullptr && node->vert != v2){
                node->next = new EdgeNode;
                node->next->next = nullptr;
                node->next->vert = v2;
                m_numEdges++;
            }
            else if (node->next->vert != v2){ //Avoid adding the same vertex two times
                EdgeNode* newVertex = new EdgeNode;
                newVertex->vert = v2;
                newVertex->next = node->next;
                node->next = newVertex;
                m_numEdges++;
            }
        }
    }
}

//O(V) because in worst case it goes trought every edge in a vertex
void GraphAdjList::removeEdge(vertex v1, vertex v2){
    if(v1 >= 0 && v1 < m_numVertices && v2 >= 0 && v2 <m_numVertices){
        EdgeNode* node = m_edges[v1];
        if(node == nullptr) return;
        else if(node->vert == v2){
            m_edges[v1] = node->next;
            delete node;
            m_numEdges--;
        }
        else{
            while(node->next != nullptr){
                if(node->next->vert == v2){
                    EdgeNode* old = node->next;
                    node->next = old->next;
                    delete old;
                    m_numEdges--;
                    break;
                }
            }
        }
    }
}

//O(V + E)
void GraphAdjList::print(){
    cout << m_numEdges << " [ ";
    for (vertex i = 0; i < m_numVertices; i++){
        EdgeNode* node = m_edges[i]; //Get the list head of edges for that vertex
        while (node != nullptr) { //And goes printing everything
            cout << "(" << i << " " << node->vert << " 1) ";
            node = node->next;
        }
    }
    cout << "]" << endl;
}

//O(E + E') bacause it passes through each edge of the two graphs
bool GraphAdjList::isSubGraph(GraphAdjList& H) {
    EdgeNode** hEdges = H.edges();
    for (vertex i = 0; i < m_numVertices; i++){
        EdgeNode* hEdge = hEdges[i];
        EdgeNode* gEdge = m_edges[i];
        while (hEdge) {
            while (gEdge != nullptr && gEdge->vert < hEdge->vert){
                gEdge = gEdge->next;
            }
            if(gEdge == nullptr){
                return false;
            }
            else if (gEdge->vert != hEdge->vert){
                return false;
            }
            hEdge = hEdge->next;
        }
    }
    return true;
}

//O(n * V) because it checks, for each step in the path, if an edge exists. Checking the existence of an edge can take len(V)
bool GraphAdjList::isValidPath(vertex path[], int iLength, bool& hasCycle){
    if (iLength < 2) return false;
    bool visited[m_numVertices];
    for(vertex i = 0; i <m_numVertices; i++) {visited[i] = false;}
    visited[path[0]] = true;

    for(int i = 1; i < iLength; i++){
        if (visited[path[i]]) hasCycle = true;

        EdgeNode* node = m_edges[path[i-1]];
        bool exists = false;
        while(node){
            if(node->vert == path[i]){
                exists = true;
                break;
            }
            node = node->next;
        }
        if(!exists){
            return false;
        }
        visited[path[i]] = true;
    }
    return true;
}

int main(){
    vertex path1[] = {0, 2, 4, 1};
    vertex path2[] = {0, 2, 4, 1, 5};
    vertex path3[] = {0, 2, 4, 1, 4, 1};
    bool p1cycle = false;
    bool p2cycle = false;
    bool p3cycle = false;

    GraphMatrix g1 = GraphMatrix(6);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(1, 4);
    g1.addEdge(2, 4);
    g1.addEdge(3, 4);
    g1.addEdge(4, 5);
    g1.addEdge(4, 1);
    g1.print();
    g1.printMatrix();

    cout << endl;
    cout << "path1 é caminho? " << g1.isValidPath(path1, 4, p1cycle) << " Com ciclo? " << p1cycle << endl;
    cout << "path2 é caminho? " << g1.isValidPath(path2, 5, p2cycle) << " Com ciclo? " << p2cycle << endl;
    cout << "path3 é caminho? " << g1.isValidPath(path3, 6, p3cycle) << " Com ciclo? " << p3cycle << endl;

    GraphMatrix g2 = GraphMatrix(6);
    g2.addEdge(0, 1);
    g2.addEdge(1, 3);
    g2.addEdge(2, 4);
    g2.addEdge(4, 5);
    g2.addEdge(4, 1);

    cout << endl;
    cout << "g2 é subgrafo? " << g1.isSubGraph(g2) << endl;
    g2.addEdge(3, 5);
    cout << "novo g2 é subgrafo? " << g1.isSubGraph(g2) << endl;

    cout << endl;
    cout << "tem caminho de 0 a 5? " << g1.hasPath(0, 5) << endl;
    cout << "tem caminho de 5 a 2? " << g1.hasPath(5, 2) << endl;
    cout << "tem caminho de 1 a 4? " << g1.hasPath(1, 4) << endl;
    bool hasPathTo[6];
    for(int i = 0; i < 6; i++){hasPathTo[i] = false;}
    g1.findConnected(1, hasPathTo);
    printList(hasPathTo, 6);

    int topologicalOrdering[6];
    for(int i = 0; i < 6; i++){topologicalOrdering[i] = -1;}
    cout << endl << "É topológico? " << g1.isTopological() << endl;
    cout << "Tem ordenação topológica? " << g1.hasTopologicalOrder(topologicalOrdering) << endl;
    printList(topologicalOrdering, 6);
    g1.removeEdge(4, 1);
    cout << "Agora é topológico? " << g1.isTopological() << endl << endl;

    GraphMatrix g3 = GraphMatrix(6);
    g3.addEdge(5, 0);
    g3.addEdge(5, 3);
    g3.addEdge(5, 4);
    g3.addEdge(4, 2);
    g3.addEdge(3, 0);
    g3.addEdge(3, 1);
    g3.addEdge(2, 0);
    g3.addEdge(2, 1);

    for(int i = 0; i < 6; i++){topologicalOrdering[i] = -1;}
    cout << endl << "g3 tem ordenação topológica? " << g3.hasTopologicalOrder(topologicalOrdering) << endl;
    printList(topologicalOrdering, 6);

    cout << endl << "DFS: ";
    int preOrder[6];
    int postOrder[6];
    int parents[6];
    g1.dfs(preOrder, postOrder, parents);
    cout << endl << "Pré ordem: ";
    printList(preOrder, 6);
    cout << "Pós ordem: ";
    printList(postOrder, 6);
    cout << "Hierarquia: ";
    printList(parents, 6);


    g1.removeEdge(0, 1);
    g1.removeEdge(0, 2);
    g1.removeEdge(1, 3);
    g1.removeEdge(1, 4);
    g1.removeEdge(2, 4);
    g1.removeEdge(3, 4);
    g1.removeEdge(4, 5);
    g1.removeEdge(4, 1);
    g1.removeEdge(4, 5);
    g1.print();
    g1.printMatrix();

    cout << endl;
    cout << "!-- Now to graphs made with adjacency lists --!" << endl;
    cout << endl;

    //testing everything again but for adjacency list graphs

    p1cycle = false;
    p2cycle = false;
    p3cycle = false;

    GraphAdjList g4 = GraphAdjList(6);
    g4.addEdge(0, 1);
    g4.addEdge(0, 2);
    g4.addEdge(1, 3);
    g4.addEdge(1, 4);
    g4.addEdge(2, 4);
    g4.addEdge(3, 4);
    g4.addEdge(4, 5);
    g4.addEdge(4, 1);
    g4.print();

    cout << endl;
    cout << "path1 é caminho? " << g4.isValidPath(path1, 4, p1cycle) << " Com ciclo? " << p1cycle << endl;
    cout << "path2 é caminho? " << g4.isValidPath(path2, 5, p2cycle) << " Com ciclo? " << p2cycle << endl;
    cout << "path3 é caminho? " << g4.isValidPath(path3, 6, p3cycle) << " Com ciclo? " << p3cycle << endl;

    GraphAdjList g5 = GraphAdjList(6);
    g5.addEdge(0, 1);
    g5.addEdge(1, 3);
    g5.addEdge(2, 4);
    g5.addEdge(4, 5);
    g5.addEdge(4, 1);

    cout << endl;
    cout << "g5 é subgrafo? " << g4.isSubGraph(g5) << endl;
    g5.addEdge(3, 5);
    cout << "novo g5 é subgrafo? " << g4.isSubGraph(g5) << endl;

    cout << endl;
    cout << "tem caminho de 0 a 5? " << g4.hasPath(0, 5) << endl;
    cout << "tem caminho de 5 a 2? " << g4.hasPath(5, 2) << endl;
    cout << "tem caminho de 1 a 4? " << g4.hasPath(1, 4) << endl;
    for(int i = 0; i < 6; i++){hasPathTo[i] = false;}
    g4.findConnected(1, hasPathTo);
    printList(hasPathTo, 6);

    for(int i = 0; i < 6; i++){topologicalOrdering[i] = -1;}
    cout << endl << "É topológico? " << g4.isTopological() << endl;
    cout << "Tem ordenação topológica? " << g4.hasTopologicalOrder(topologicalOrdering) << endl;
    printList(topologicalOrdering, 6);
    g4.removeEdge(4, 1);
    cout << "Agora é topológico? " << g4.isTopological() << endl;

    GraphMatrix g6 = GraphMatrix(6);
    g6.addEdge(5, 0);
    g6.addEdge(5, 3);
    g6.addEdge(5, 4);
    g6.addEdge(4, 2);
    g6.addEdge(3, 0);
    g6.addEdge(3, 1);
    g6.addEdge(2, 0);
    g6.addEdge(2, 1);

    for(int i = 0; i < 6; i++){topologicalOrdering[i] = -1;}
    cout << endl << "g6 tem ordenação topológica? " << g6.hasTopologicalOrder(topologicalOrdering) << endl;
    printList(topologicalOrdering, 6);

    cout << endl << "DFS: ";
    g4.dfs(preOrder, postOrder, parents);
    cout << endl << "Pré ordem: ";
    printList(preOrder, 6);
    cout << "Pós ordem: ";
    printList(postOrder, 6);
    cout << "Hierarquia: ";
    printList(parents, 6);


    g4.removeEdge(0, 1);
    g4.removeEdge(0, 2);
    g4.removeEdge(1, 3);
    g4.removeEdge(1, 4);
    g4.removeEdge(2, 4);
    g4.removeEdge(3, 4);
    g4.removeEdge(4, 5);
    g4.removeEdge(4, 1);
    g4.removeEdge(4, 5);
    g4.removeEdge(4, 1);
    g4.print();


}
