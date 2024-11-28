#include <iostream>
#include "structs/Graphs.h"
#include "structs/Heaps.h"
#include "structs/UnionFind.h"
#include "sorting.h"
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << "]" << endl;}

using namespace std;

//O(V^3) - could be way better but I would need to change heap implementation, a work that I can't do now even if I have a improved heap implementation.
void GraphMatrix::slowPrim(vertex parents[], vertex v0){
    const int INF = 2147483647;
    for(vertex v = 0; v < m_numVertex; v++){parents[v] = -1;}
    parents[v0] = v0;

    while(true){
        vertex v1;
        vertex v1_parent;
        int best_cost = INF;
        for(vertex v = 0; v < m_numVertex; v++){
            if (parents[v] == -1) continue;
            for(vertex v2 = 0; v2 < m_numVertex; v2++){
                if(hasEdge(v, v2) && parents[v2] == -1 && m_edges[v][v2] < best_cost){
                    best_cost = m_edges[v][v2];
                    v1 = v2;
                    v1_parent = v;
                }
            }
        }
        if(best_cost == INF) return;
        parents[v1] = v1_parent;
    }
}

//O(V^3) - again, could be better, but no time now...
void GraphMatrix::slowKruskal(vertex edges1[], vertex edges2[]){
    const int INF = 2147483647;
    vertex group[m_numVertex];
    for(vertex v = 0; v < m_numVertex; v++){edges1[v] = -1; edges2[v] = -1; group[v + 1] = v + 1;}
    group[0] = 0;
    int counter = 0;
    while(true){
        int bestV1, bestV2;
        int bestCost = INF;
        for(vertex v = 0; v < m_numVertex; v++){
            for(vertex v1 = v + 1; v1 < m_numVertex; v1++){
                if(hasEdge(v, v1) && group[v] != group[v1] && m_edges[v][v1] < bestCost){
                    bestV1 = v;
                    bestV2 = v1;
                    bestCost = m_edges[v][v1];
                }
            }
        }
        if(bestCost == INF) break;
        edges1[counter] = bestV1;
        edges2[counter] = bestV2;
        counter++;
        for(vertex v = 0; v < m_numVertex; v++){
            if(group[v] == group[bestV2]){
                group[v] = group[bestV1];
            }
        }
    }
}



//O(VE) - could be way better but I would need to change heap implementation, a work that I can't do now even if I have a improved heap implementation.
void GraphAdjList::slowPrim(vertex parents[], vertex v0){
    const int INF = 2147483647;
    for(vertex v = 0; v < m_numVertex; v++){parents[v] = -1;}
    parents[v0] = v0;

    while(true){
        vertex v1;
        vertex v1Parent;
        int bestCost = INF;
        for(vertex v = 0; v < m_numVertex; v++){
            if (parents[v] == -1) continue;
            EdgeNode* node = m_edges[v];
            while(node){
                if(parents[node->vert] == -1 && node->weight < bestCost){
                    bestCost = node->weight;
                    v1 = node->vert;
                    v1Parent = v;
                }
                node = node->next;
            }
        }
        if(bestCost == INF) break;
        parents[v1] = v1Parent;
    }
}

//O(V(V + E)) - again, could be better, but no time now...
void GraphAdjList::slowKruskal(vertex edges1[], vertex edges2[]){
    const int INF = 2147483647;
    vertex group[m_numVertex];
    for(vertex v = 0; v < m_numVertex; v++){edges1[v] = -1; edges2[v] = -1; group[v + 1] = v + 1;}
    group[0] = 0;
    int counter = 0;
    while(true){
        int bestV1, bestV2;
        int bestCost = INF;
        for(vertex v = 0; v < m_numVertex; v++){
            EdgeNode* node = m_edges[v];
            while(node){
                if(v < node->vert && group[v] != group[node->vert] && node->weight < bestCost){
                    bestV1 = v;
                    bestV2 = node->vert;
                    bestCost = node->weight;
                }
                node = node->next;
            }
        }
        if(bestCost == INF) break;
        edges1[counter] = bestV1;
        edges2[counter] = bestV2;
        counter++;
        for(vertex v = 0; v < m_numVertex; v++){
            if(group[v] == group[bestV2]){
                group[v] = group[bestV1];
            }
        }
    }
}
/*
int main(){
    GraphMatrix g1 = GraphMatrix(6);
    g1.addEdge(0, 1, 7); g1.addEdge(1, 0, 7);
    g1.addEdge(0, 2, 9); g1.addEdge(2, 0, 9);
    g1.addEdge(1, 2, 5); g1.addEdge(2, 1, 5);
    g1.addEdge(1, 3, 2); g1.addEdge(3, 1, 2);
    g1.addEdge(1, 4, 4); g1.addEdge(4, 1, 4);
    g1.addEdge(2, 4, 6); g1.addEdge(4, 2, 6);
    g1.addEdge(2, 5, 1); g1.addEdge(5, 2, 1);
    g1.addEdge(3, 4, 3); g1.addEdge(4, 3, 3);
    g1.addEdge(3, 5, 2); g1.addEdge(5, 3, 2);
    g1.addEdge(4, 5, 7); g1.addEdge(5, 4, 7);
    g1.print();
    cout << endl;

    vertex parents[6];
    g1.slowPrim(parents);
    cout << "MST gerada por prim com inicio em 0: ";
    printList(parents, 6);

    g1.slowPrim(parents, 1);
    cout << "MST gerada por prim com inicio em 1: ";
    printList(parents, 6);

    vertex edges1[5];
    vertex edges2[5];
    g1.slowKruskal(edges1, edges2);
    cout << "MST gerada por kruskal: " << endl;
    printList(edges1, 5);
    printList(edges2, 5);

    cout << endl;
    cout << "!-- Agora para grafos feitos com listas de adjacência --!" << endl;
    cout << endl;

    //testing everything again but for adjacency list graphs

    GraphAdjList g5 = GraphAdjList(6);
    g5.addEdge(0, 1, 7); g5.addEdge(1, 0, 7);
    g5.addEdge(0, 2, 9); g5.addEdge(2, 0, 9);
    g5.addEdge(1, 2, 5); g5.addEdge(2, 1, 5);
    g5.addEdge(1, 3, 2); g5.addEdge(3, 1, 2);
    g5.addEdge(1, 4, 4); g5.addEdge(4, 1, 4);
    g5.addEdge(2, 4, 6); g5.addEdge(4, 2, 6);
    g5.addEdge(2, 5, 1); g5.addEdge(5, 2, 1);
    g5.addEdge(3, 4, 3); g5.addEdge(4, 3, 3);
    g5.addEdge(3, 5, 2); g5.addEdge(5, 3, 2);
    g5.addEdge(4, 5, 7); g5.addEdge(5, 4, 7);
    g5.print(); cout << endl;

    g5.slowPrim(parents);
    cout << "MST gerada por prim com inicio em 0: ";
    printList(parents, 6);

    g5.slowPrim(parents, 1);
    cout << "MST gerada por prim com inicio em 1: ";
    printList(parents, 6);

    g5.slowKruskal(edges1, edges2);
    cout << "MST gerada por kruskal: " << endl;
    printList(edges1, 5);
    printList(edges2, 5);

}
*/
