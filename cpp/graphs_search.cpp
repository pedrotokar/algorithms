#include <iostream>
#include "structs/Graphs.h"
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << " ]" << endl;}

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



void GraphMatrix::dfsRecursive(vertex v1, int preOrder[], int& preCount, int postOrder[], int& postCount, int parents[]){
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
void GraphMatrix::dfs(int preOrder[], int postOrder[], int parents[]){
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
void GraphMatrix::bfsTree(vertex v0, int order[], int parents[]){
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
void GraphAdjList::bfsTree(vertex v0, int order[], int parents[]){
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
