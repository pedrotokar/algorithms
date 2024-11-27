#include <iostream>
#include "structs/Graphs.h"
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << "]" << endl;}

using namespace std;


//theta(V^2) - it may seems like it's more complex, but since we have the hasPath array, we can ensure that each vertex is visited only once.
void GraphMatrix::findConnected(vertex v1, bool hasPath[]){ //finds EVERY vertex that can be reached starting from v1
    hasPath[v1] = true;
    for (vertex v2 = 0; v2 < m_numVertex; v2++){
        if(hasEdge(v1, v2) && !hasPath[v2]){ //O(V)
            findConnected(v2, hasPath); //calls this exactly one time per vertex
        }
    }
}

//theta(V^2) - Just envelops above function to get the result from one specific vertex
bool GraphMatrix::hasPath(vertex v1, vertex v2){
    bool visited[m_numVertex];
    for (vertex v = 0; v < m_numVertex; v++){
        visited[v] = false;
    }
    findConnected(v1, visited);
    return visited[v2];
}



void GraphMatrix::dfsRecursive(vertex v1, int preOrder[], int& preCount, int postOrder[], int& postCount, vertex parents[]){
    preOrder[v1] = preCount++;
    for (vertex v2 = 0; v2 < m_numVertex; v2++){
        if(hasEdge(v1, v2) && preOrder[v2] == -1){
            parents[v2] = v1;
            dfsRecursive(v2, preOrder, preCount, postOrder, postCount, parents);
        }
    }
    postOrder[v1] = postCount++;
}

//Returns preOrder, postOrder and radical forest of any graph
void GraphMatrix::dfs(int preOrder[], int postOrder[], vertex parents[]){
    int preCount = 0;
    int postCount = 0;
    for (vertex v = 0; v < m_numVertex; v++){
        preOrder[v] = -1;
        postOrder[v] = -1;
        parents[v] = -1;
    }
    for (vertex v = 0; v < m_numVertex; v++){
        int depth = 0;
        if(preOrder[v] == -1){
            parents[v] = v;
            dfsRecursive(v, preOrder, preCount, postOrder, postCount, parents);
        }
    }
}

//O(V^2)
bool GraphMatrix::isTopological(){
    for(vertex i = 0; i < m_numVertex; i++){
        for(vertex j = 0; j < i; j++){
            if(hasEdge(i, j)){
                return false;
            }
        }
    }
    return true;
}

//O(V^2)
bool GraphMatrix::hasTopologicalOrder(vertex ordering[]){
    int inDegree[m_numVertex]; //Number of edges "entering" each vertex
    for(vertex i = 0; i < m_numVertex; i++) {inDegree[i] = 0;}
    for(vertex i = 0; i < m_numVertex; i++) {                 //O(V^2)
        for(vertex j = 0; j < m_numVertex; j++) {
            if(hasEdge(i, j)) inDegree[j]++;
        }
    }
    vertex queue[m_numVertex]; //Queue to list vertex we should visit, in order
    int queueStart = 0;
    int queueEnd = 0;
    for(vertex i = 0; i < m_numVertex; i++) { //adds to queue all vertex that has no incoming edges (sources)
        if(inDegree[i] == 0){
            queue[queueEnd] = i;
            queueEnd++;
        }
    }
    int counter = 0; //counts how many vertex have been visited already
    while (queueStart < queueEnd){ //O(V)
        vertex current = queue[queueStart]; //takes the vertex in queue
        queueStart++;
        ordering[current] = counter; //Assigns a topological position to that vertex
        counter++;
        for(vertex next = 0; next < m_numVertex; next++){ //for each vertex that met the conditions of having no entering edges, "removes" the edges that comes from this vertex, having the same effect as erasing the vertex. If a vertex begins to have entering degree 0 after that, adds to the queue
            if(hasEdge(current, next)){
                inDegree[next]--;
                if(inDegree[next] == 0){
                    queue[queueEnd] = next;
                    queueEnd++;
                }
            }
        }
    }
    return counter >= m_numVertex; //if it's smaller, means we havent visited all the vertex
}


//theta(V^2) - every vertex gets queued once, and for each vertex we run in all of its edges (which equals to running in all vertexes)
void GraphMatrix::bfsForest(int order[]){
    for(vertex v = 0; v < m_numVertex; v++){order[v] = -1;}
    int counter = 0;
    for(vertex v = 0; v < m_numVertex; v++){ //already found
        if(order[v] != -1){
            continue;
        }
        vertex queue[m_numVertex];
        int queueStart = 0;
        int queueEnd = 0;
        queue[queueEnd++] = v;
        order[v] = counter++;
        while(queueEnd > queueStart){
            vertex current = queue[queueStart++];
            for(vertex next = 0; next < m_numVertex; next++){
                if (hasEdge(current, next) && order[next] == -1){
                    order[next] = counter++;
                    queue[queueEnd++] = next;
                }
            }
        }
    }
}

//O(V^2) - not all the vertex gets queued, and for each queued vertex we run in all of its edges (which equals to running in all vertexes)
//The difference between the forest and this is that this one finds a tree associated with the inputed vertex
void GraphMatrix::bfsTree(vertex v0, int order[], vertex parents[]){
    for(vertex v = 0; v < m_numVertex; v++){order[v] = -1; parents[v] = -1;}

    int counter = 0;
    vertex queue[m_numVertex];
    int queueStart = 0;
    int queueEnd = 0;
    queue[queueEnd++] = v0;
    order[v0] = counter++;
    parents[v0] = v0;

    while(queueEnd > queueStart){
        vertex current = queue[queueStart++];
        for(vertex next = 0; next < m_numVertex; next++){
            if (hasEdge(current, next) && order[next] == -1){
                order[next] = counter++;
                parents[next] = current;
                queue[queueEnd++] = next;
            }
        }
    }
}


//Implements everything but now for adjacency list graphs-------------------------------------------------------


//O(V + E) -
void GraphAdjList::findConnected(vertex v1, bool hasPath[]){ //finds EVERY vertex that can be reached starting from v1
    hasPath[v1] = true;
    EdgeNode* node = m_edges[v1];
    while(node){
        if(!hasPath[node->vert]){
            findConnected(node->vert, hasPath); //calls exactly one time per vertex
        }
        node = node->next;
    }
}

//O(V + E) envelops above function
bool GraphAdjList::hasPath(vertex v1, vertex v2){
    bool visited[m_numVertex];
    for (vertex v = 0; v < m_numVertex; v++){
        visited[v] = false;
    }
    findConnected(v1, visited);
    return visited[v2];
}



void GraphAdjList::dfsRecursive(vertex v1, int preOrder[], int& preCount, int postOrder[], int& postCount, vertex parents[]){
    preOrder[v1] = preCount++;
    EdgeNode* node = m_edges[v1];
    while(node){
        if(preOrder[node->vert] == -1){
            parents[node->vert] = v1;
            dfsRecursive(node->vert, preOrder, preCount, postOrder, postCount, parents);
        }
        node = node->next;
    }
    postOrder[v1] = postCount++;
}

void GraphAdjList::dfs(int preOrder[], int postOrder[], vertex parents[]){
    int preCount = 0;
    int postCount = 0;
    for (vertex v = 0; v < m_numVertex; v++){
        preOrder[v] = -1;
        postOrder[v] = -1;
        parents[v] = -1;
    }
    for (vertex v = 0; v < m_numVertex; v++){
        if(preOrder[v] == -1){
            parents[v] = v;
            dfsRecursive(v, preOrder, preCount, postOrder, postCount, parents);
        }
    }
}


//O(V^2)
bool GraphAdjList::isTopological(){ //If the list is always ordered, complexity can be lower
    for (vertex i = 0; i <m_numVertex; i++){
        EdgeNode* node = m_edges[i];
        while(node){
            if(i >= node->vert){
                return false;
            }
            node = node->next;
        }
    }
    return true;
}


//O(V + E)
bool GraphAdjList::hasTopologicalOrder(vertex ordering[]){
    int inDegree[m_numVertex]; //Number of edges "entering" each vertex
    for(vertex i = 0; i < m_numVertex; i++) {inDegree[i] = 0;}
    for(vertex i = 0; i < m_numVertex; i++) {                 //O(V + E)
        EdgeNode* node = m_edges[i];
        while(node) {
            inDegree[node->vert]++;
            node = node->next;
        }
    }
    vertex queue[m_numVertex]; //Queue to list vertex we should visit, in order
    int queueStart = 0;
    int queueEnd = 0;
    for(vertex i = 0; i < m_numVertex; i++) { //adds to queue all vertex that has no incoming edges (sources)
        if(inDegree[i] == 0){
            queue[queueEnd] = i;
            queueEnd++;
        }
    }
    int counter = 0; //counts how many vertex have been visited already
    while (queueStart < queueEnd){ //O(V)
        vertex current = queue[queueStart]; //takes the vertex in queue
        queueStart++;
        ordering[current] = counter; //Assigns a topological position to that vertex
        counter++;
        EdgeNode* node = m_edges[current];
        while(node){ //O(E)
            inDegree[node->vert]--;
            if(inDegree[node->vert] == 0){
                queue[queueEnd] = node->vert;
                queueEnd++;
            }
            node = node->next;
        }
    }
    return counter >= m_numVertex; //if it's smaller, means we havent visited all the vertex
}

//theta(V + E) - every vertex gets queued once, and for each vertex we run in all of its edges
void GraphAdjList::bfsForest(int order[]){
    for(vertex v = 0; v < m_numVertex; v++){order[v] = -1;}
    int counter = 0;
    for(vertex v = 0; v < m_numVertex; v++){ //already found
        if(order[v] != -1){
            continue;
        }
        vertex queue[m_numVertex];
        int queueStart = 0;
        int queueEnd = 0;
        queue[queueEnd++] = v;
        order[v] = counter++;
        while(queueEnd > queueStart){
            vertex current = queue[queueStart++];
            EdgeNode* node = m_edges[current];
            while(node){
                if (order[node->vert] == -1){
                    order[node->vert] = counter++;
                    queue[queueEnd++] = node->vert;
                }
                node = node->next;
            }
        }
    }
}

//O(V + E) - not all the vertex gets queued, and for each queued vertex we run in all of its edges
//The difference between the forest and this is that this one finds a tree associated with the inputed vertex
void GraphAdjList::bfsTree(vertex v0, int order[], vertex parents[]){
    for(vertex v = 0; v < m_numVertex; v++){order[v] = -1; parents[v] = -1;}

    int counter = 0;
    vertex queue[m_numVertex];
    int queueStart = 0;
    int queueEnd = 0;
    queue[queueEnd++] = v0;
    order[v0] = counter++;
    parents[v0] = v0;

    while(queueEnd > queueStart){
        vertex current = queue[queueStart++];
        EdgeNode* node = m_edges[current];
        while(node){
            if (order[node->vert] == -1){
                order[node->vert] = counter++;
                parents[node->vert] = current;
                queue[queueEnd++] = node->vert;
            }
            node = node->next;
        }
    }
}

/*
int main(){
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
    cout << endl;

    cout << "tem caminho de 0 a 5? " << g1.hasPath(0, 5) << endl;
    cout << "tem caminho de 5 a 2? " << g1.hasPath(5, 2) << endl;
    cout << "tem caminho de 1 a 4? " << g1.hasPath(1, 4) << endl;

    bool hasPathTo[6];
    for(int i = 0; i < 6; i++){hasPathTo[i] = false;}
    g1.findConnected(1, hasPathTo);
    cout << "1 se conecta para: ";
    printList(hasPathTo, 6);

    cout << endl <<"Topologia";
    int topologicalOrdering[6];
    for(int i = 0; i < 6; i++){topologicalOrdering[i] = -1;}
    cout << endl << "g1 é topológico? " << g1.isTopological() << endl;
    cout << "Tem ordenação topológica? " << g1.hasTopologicalOrder(topologicalOrdering) << endl;
    printList(topologicalOrdering, 6);
    g1.removeEdge(4, 1);
    cout << "Agora é topológico? " << g1.isTopological() << endl;

    g1.addEdge(4, 1);

    GraphMatrix g2 = GraphMatrix(6);
    g2.addEdge(5, 0);
    g2.addEdge(5, 3);
    g2.addEdge(5, 4);
    g2.addEdge(4, 2);
    g2.addEdge(3, 0);
    g2.addEdge(3, 1);
    g2.addEdge(2, 0);
    g2.addEdge(2, 1);

    for(int i = 0; i < 6; i++){topologicalOrdering[i] = -1;}
    cout << endl << "g3 tem ordenação topológica? " << g2.hasTopologicalOrder(topologicalOrdering) << endl;
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
    cout << "Floresta DFS: ";
    printList(parents, 6);

    cout << endl << "BFS: ";
    int bfsOrder[6];
    for(int i = 0; i < 6; i++){bfsOrder[i] = 0;}
    g1.bfsForest(bfsOrder);
    cout << endl << "Ordem BFS (completo): ";
    printList(bfsOrder, 6);

    for(int i = 0; i < 6; i++){bfsOrder[i] = 0; parents[i] = 0;}
    g1.bfsTree(2, bfsOrder, parents);
    cout << endl << "Ordem BFS (árvore com raiz em 2): ";
    printList(bfsOrder, 6);
    cout << "Árvore";
    printList(parents, 6);

    for(int i = 0; i < 6; i++){bfsOrder[i] = 0; parents[i] = 0;}
    g1.bfsTree(4, bfsOrder, parents);
    cout << endl << "Ordem BFS (árvore com raiz em 4): ";
    printList(bfsOrder, 6);
    cout << "Árvore: ";
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

    cout << endl;
    cout << "!-- Agora para grafos feitos com listas de adjacência --!" << endl;
    cout << endl;

    //testing everything again but for adjacency list graphs

    GraphAdjList g3 = GraphAdjList(6);
    g3.addEdge(0, 1);
    g3.addEdge(0, 2);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(2, 4);
    g3.addEdge(3, 4);
    g3.addEdge(4, 5);
    g3.addEdge(4, 1);
    g3.print();
    cout << endl;

    cout << endl;
    cout << "tem caminho de 0 a 5? " << g3.hasPath(0, 5) << endl;
    cout << "tem caminho de 5 a 2? " << g3.hasPath(5, 2) << endl;
    cout << "tem caminho de 1 a 4? " << g3.hasPath(1, 4) << endl;

    for(int i = 0; i < 6; i++){hasPathTo[i] = false;}
    cout << "1 se conecta para: ";
    g3.findConnected(1, hasPathTo);
    printList(hasPathTo, 6);

    for(int i = 0; i < 6; i++){topologicalOrdering[i] = -1;}
    cout << endl << "g1 é topológico? " << g3.isTopological() << endl;
    cout << "Tem ordenação topológica? " << g3.hasTopologicalOrder(topologicalOrdering) << endl;
    printList(topologicalOrdering, 6);
    g3.removeEdge(4, 1);
    cout << "Agora é topológico? " << g3.isTopological() << endl;
    for(int i = 0; i < 6; i++){topologicalOrdering[i] = -1;}

    g3.addEdge(4, 1);

    GraphAdjList g4 = GraphAdjList(6);
    g4.addEdge(5, 0);
    g4.addEdge(5, 3);
    g4.addEdge(5, 4);
    g4.addEdge(4, 2);
    g4.addEdge(3, 0);
    g4.addEdge(3, 1);
    g4.addEdge(2, 0);
    g4.addEdge(2, 1);

    for(int i = 0; i < 6; i++){topologicalOrdering[i] = -1;}
    cout << endl << "g4 tem ordenação topológica? " << g4.hasTopologicalOrder(topologicalOrdering) << endl;
    printList(topologicalOrdering, 6);


    cout << endl << "DFS: ";
    g3.dfs(preOrder, postOrder, parents);
    cout << endl << "Pré ordem: ";
    printList(preOrder, 6);
    cout << "Pós ordem: ";
    printList(postOrder, 6);
    cout << "Floresta DFS: ";
    printList(parents, 6);

    cout << endl << "BFS: ";
    for(int i = 0; i < 6; i++){bfsOrder[i] = 0;}
    g3.bfsForest(bfsOrder);
    cout << endl << "Ordem BFS (completo): ";
    printList(bfsOrder, 6);

    for(int i = 0; i < 6; i++){bfsOrder[i] = 0; parents[i] = 0;}
    g3.bfsTree(2, bfsOrder, parents);
    cout << endl << "Ordem BFS (árvore com raiz em 2): ";
    printList(bfsOrder, 6);
    cout << "Árvore: ";
    printList(parents, 6);

    for(int i = 0; i < 6; i++){bfsOrder[i] = 0; parents[i] = 0;}
    g3.bfsTree(4, bfsOrder, parents);
    cout << endl << "Ordem BFS (árvore com raiz em 4): ";
    printList(bfsOrder, 6);
    cout << "Árvore: ";
    printList(parents, 6);

}


*/
