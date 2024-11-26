#include <iostream>
#include "structs/Graphs.h"
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << " ]" << endl;}

using namespace std;

//theta(V + E)
void GraphAdjList::dagSPT(vertex parents[], int distances[]){
    const int INF = m_numVertex + 1;
    for(vertex v = 0; v < m_numVertex; v++){distances[v] = INF; parents[v] = -1;}
    int topologicalOrdering[m_numVertex];
    if(hasTopologicalOrder(topologicalOrdering)){ //theta(V + E) operation to check if able to do
        int topoAux[m_numVertex];
        for (vertex v1 = 0; v1 < m_numVertex; v1++){ //theta(V) - uncessary if you assume prior topological ordering.
            topoAux[topologicalOrdering[v1]] = v1;
        }
        distances[topoAux[0]] = 0;
        parents[topoAux[0]] = topoAux[0];
        for (vertex v1 = 0; v1 < m_numVertex; v1++){ //)theta(V), and iteration trough edges gives theta(V + E)
            EdgeNode* node = m_edges[topoAux[v1]];
            while(node){
                if (distances[topoAux[v1]] + 1 <= distances[node->vert]){
                    parents[node->vert] = topoAux[v1];
                    distances[node->vert] = distances[topoAux[v1]] + 1;
                }
                node = node->next;
            }
        }
    }
}

//O(V + E) - almost same thing as a BFS, generates PST from any vertex
void GraphAdjList::SPT(vertex v0, vertex parents[], int distances[]){
    const int INF = m_numVertex + 1;
    for(vertex v = 0; v < m_numVertex; v++){distances[v] = INF; parents[v] = -1;}

    vertex queue[m_numVertex];
    int queueStart = 0;
    int queueEnd = 0;
    queue[queueEnd++] = v0;
    distances[v0] = 0;
    parents[v0] = v0;

    while(queueEnd > queueStart){
        vertex current = queue[queueStart++];
        EdgeNode* node = m_edges[current];
        while(node){
            if (distances[node->vert] == INF){
                distances[node->vert] = distances[current] + 1;
                parents[node->vert] = current;
                queue[queueEnd++] = node->vert;
            }
            node = node->next;
        }
    }
}

