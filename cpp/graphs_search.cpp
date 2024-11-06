#include <iostream>
#include "structs/Graphs.h"
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << " ]" << endl;}

using namespace std;


//theta(V^2)
void GraphMatrix::findConnected(vertex v1, bool hasPath[]){ //finds EVERY vertex that can be reached starting from v1
    hasPath[v1] = true;
    for (vertex v2 = 0; v2 < m_numVertices; v2++){
        if(hasEdge(v1, v2) && !hasPath[v2]){ //O(V)
            findConnected(v2, hasPath); //calls this exactly one time per vertex
        }
    }
}

//theta(V^2) - Just envelops above function to get the result from one specific vertex
bool GraphMatrix::hasPath(vertex v1, vertex v2){
    bool visited[m_numVertices];
    for (vertex v = 0; v < m_numVertices; v++){
        visited[v] = false;
    }
    findConnected(v1, visited);
    return visited[v2];
}



void GraphMatrix::dfsRecursive(vertex v1, int preOrder[], int& preCount, int postOrder[], int& postCount, int parents[]){
    preOrder[v1] = preCount++;
    for (vertex v2 = 0; v2 < m_numVertices; v2++){
        if(hasEdge(v1, v2) && preOrder[v2] == -1){
            parents[v2] = v1;
            dfsRecursive(v2, preOrder, preCount, postOrder, postCount, parents);
        }
    }
    postOrder[v1] = postCount++;
}

//Returns preOrder, postOrder and radical forest of any graph
void GraphMatrix::dfs(int preOrder[], int postOrder[], int parents[]){
    int preCount = 0;
    int postCount = 0;
    for (vertex v = 0; v < m_numVertices; v++){
        preOrder[v] = -1;
        postOrder[v] = -1;
        parents[v] = -1;
    }
    for (vertex v = 0; v < m_numVertices; v++){
        int depth = 0;
        if(preOrder[v] == -1){
            parents[v] = v;
            dfsRecursive(v, preOrder, preCount, postOrder, postCount, parents);
        }
    }
}

//O(V^2)
bool GraphMatrix::isTopological(){
    for(vertex i = 0; i < m_numVertices; i++){
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
    int inDegree[m_numVertices]; //Number of edges "entering" each vertex
    for(vertex i = 0; i < m_numVertices; i++) {inDegree[i] = 0;}
    for(vertex i = 0; i < m_numVertices; i++) {                 //O(V^2)
        for(vertex j = 0; j < m_numVertices; j++) {
            if(hasEdge(i, j)) inDegree[j]++;
        }
    }
    vertex queue[m_numVertices]; //Queue to list vertex we should visit, in order
    int queueStart= 0;
    int queueEnd = 0;
    for(vertex i = 0; i < m_numVertices; i++) { //adds to queue all vertex that has no incoming edges (sources)
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
        for(vertex next = 0; next < m_numVertices; next++){ //for each vertex that met the conditions of having no entering edges, "removes" the edges that comes from this vertex, having the same effect as erasing the vertex. If a vertex begins to have entering degree 0 after that, adds to the queue
            if(hasEdge(current, next)){
                inDegree[next]--;
                if(inDegree[next] == 0){
                    queue[queueEnd] = next;
                    queueEnd++;
                }
            }
        }
    }
    return counter >= m_numVertices; //if it's smaller, means we havent visited all the vertex
}


//Implements everything but now for adjacency list graphs-------------------------------------------------------



//O(V + E)
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
    bool visited[m_numVertices];
    for (vertex v = 0; v < m_numVertices; v++){
        visited[v] = false;
    }
    findConnected(v1, visited);
    return visited[v2];
}



void GraphAdjList::dfsRecursive(vertex v1, int preOrder[], int& preCount, int postOrder[], int& postCount, int parents[]){
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

void GraphAdjList::dfs(int preOrder[], int postOrder[], int parents[]){
    int preCount = 0;
    int postCount = 0;
    for (vertex v = 0; v < m_numVertices; v++){
        preOrder[v] = -1;
        postOrder[v] = -1;
        parents[v] = -1;
    }
    for (vertex v = 0; v < m_numVertices; v++){
        if(preOrder[v] == -1){
            parents[v] = v;
            dfsRecursive(v, preOrder, preCount, postOrder, postCount, parents);
        }
    }
}


//O(V^2)
bool GraphAdjList::isTopological(){ //If the list is always ordered, complexity can be lower
    for (vertex i = 0; i <m_numVertices; i++){
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
    int inDegree[m_numVertices]; //Number of edges "entering" each vertex
    for(vertex i = 0; i < m_numVertices; i++) {inDegree[i] = 0;}
    for(vertex i = 0; i < m_numVertices; i++) {                 //O(V + E)
        EdgeNode* node = m_edges[i];
        while(node) {
            inDegree[node->vert]++;
            node = node->next;
        }
    }
    vertex queue[m_numVertices]; //Queue to list vertex we should visit, in order
    int queueStart= 0;
    int queueEnd = 0;
    for(vertex i = 0; i < m_numVertices; i++) { //adds to queue all vertex that has no incoming edges (sources)
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
    return counter >= m_numVertices; //if it's smaller, means we havent visited all the vertex
}
