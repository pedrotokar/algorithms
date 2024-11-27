#include <iostream>
#include "structs/Graphs.h"
#include "structs/Heaps.h"
#define printList(v, n) {cout << "[ "; for (int i = 0; i < n; i++) { cout << v[i] << " "; }; cout << " ]" << endl;}

using namespace std;

//theta(V^2)
void GraphMatrix::dagSPT(vertex parents[], int distances[]){
    const int INF = m_numVertex + 1;
    for(vertex v = 0; v < m_numVertex; v++){distances[v] = INF; parents[v] = -1;}
    int topologicalOrdering[m_numVertex];
    if(hasTopologicalOrder(topologicalOrdering)){ //theta(V^2) operation to check if able to do
        int topoAux[m_numVertex];
        for (vertex v1 = 0; v1 < m_numVertex; v1++){ //theta(V) - uncessary if you assume prior topological ordering.
            topoAux[topologicalOrdering[v1]] = v1;
        }
        distances[topoAux[0]] = 0;
        parents[topoAux[0]] = topoAux[0];
        for (vertex v1 = 0; v1 < m_numVertex; v1++){ //)theta(V), and iteration trough edges gives theta(V^2) since in matrix this means iterating thourgh all the vertexes in two loops
            for(vertex v2 = 0; v2 < m_numVertex; v2++){
                if(hasEdge(topoAux[v1], topoAux[v2]) && distances[topoAux[v1]] + 1 <= distances[topoAux[v2]]){
                    parents[topoAux[v2]] = topoAux[v1];
                    distances[topoAux[v2]] = distances[topoAux[v1]] + 1;
                }
            }
        }
    }
}

//O(V^2) - almost same thing as a BFS, generates PST from any vertex
void GraphMatrix::SPT(vertex v0, vertex parents[], int distances[]){
    const int INF = m_numVertex + 1;
    for(vertex v = 0; v < m_numVertex; v++){distances[v] = INF; parents[v] = -1;}

    vertex queue[m_numVertex];
    int queueStart = 0;
    int queueEnd = 0;
    queue[queueEnd++] = v0;
    distances[v0] = 0;
    parents[v0] = v0;

    while(queueEnd > queueStart){
        vertex v1 = queue[queueStart++];
        for(vertex v2 = 0; v2 < m_numVertex; v2++){
            if (hasEdge(v1,v2) && distances[v2] == INF){
                distances[v2] = distances[v1] + 1;
                parents[v2] = v1;
                queue[queueEnd++] = v2;
            }
        }
    }
}

//O((V^2)log(V)) - does the habitual scan in all the vertices and edges, but additionaly keeps
//a heap, which has O(log(V)) insertion and remotion operations.
void GraphMatrix::CPTDijkstra(vertex v0, vertex parents[], int distance[]){
    const int INF = 2147483647;
    bool visited[m_numVertex];
    for(vertex v = 0; v < m_numVertex; v++){
        parents[v] = -1;
        distance[v] = INF;
        visited[v] = false;
    }

    distance[v0] = 0;
    parents[v0] = v0;

    vertex heap[m_numVertex];
    int heapEnd = 0;
    heap[heapEnd++] = v0;

    while(heapEnd != 0){
        vertex v1 = heap[0]; //removing v1 from heap
        heapEnd--;
        swap(heap, 0, heapEnd);
        minHeapify(heap, heapEnd, 0, distance);
        if(distance[v1] == INF) break;

        for (vertex v2 = 0; v2 < m_numVertex; v2++){
            if(hasEdge(v1, v2) && !visited[v2]){
                if (distance[v1] + m_edges[v1][v2] < distance[v2]){
                    distance[v2] = distance[v1] + m_edges[v1][v2];
                    parents[v2] = v1;
                    heap[heapEnd++] = v2;
                    minHeapifyBottom(heap, heapEnd - 1, heapEnd, distance);
                }
            }
        }
        visited[v1] = true;
    }
}

//theta(v^3) - does theta(V^2) operation (checking edges) V times
bool GraphMatrix::CPTBellmanFord(vertex v0, vertex parents[], int distance[]){
    const int INF = 2147483647 - 1000000; //integer overflow may kill the algorithm - in production cases would need special care
    for(vertex v = 0; v < m_numVertex; v++){
        parents[v] = -1;
        distance[v] = INF;
    }

    distance[v0] = 0;
    parents[v0] = v0;

    for(int i = 0; i < m_numVertex - 1; i++){ //theta(V)
        for(vertex v1 = 0; v1 < m_numVertex; v1++){ //theta(V)
            for(vertex  v2 = 0; v2 < m_numVertex; v2++){ //theta(V^3)
                if (hasEdge(v1, v2) && distance[v1] + m_edges[v1][v2] < distance[v2]){ //relaxing the edges
                    distance[v2] = distance[v1] + m_edges[v1][v2];
                    parents[v2] = v1;
                }
            }
        }
    }

    for(int v1 = 0; v1 < m_numVertex; v1++){
        for(vertex  v2 = 0; v2 < m_numVertex; v2++){
            if (hasEdge(v1, v2) && distance[v1] + m_edges[v1][v2] < distance[v2]){ //relaxing the edges
                return false;
            }
        }
    }
    return true;
}

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

//O((V + E)log(V)) - does the habitual scan in all the vertices and edges, but additionaly keeps
//a heap, which has O(log(V)) insertion and remotion operations.
void GraphAdjList::CPTDijkstra(vertex v0, vertex parents[], int distance[]){
    const int INF = 2147483647;
    bool visited[m_numVertex];
    for(vertex v = 0; v < m_numVertex; v++){
        parents[v] = -1;
        distance[v] = INF;
        visited[v] = false;
    }

    distance[v0] = 0;
    parents[v0] = v0;

    vertex heap[m_numVertex];
    int heapEnd = 0;
    heap[heapEnd++] = v0;

    while(heapEnd != 0){
        vertex v1 = heap[0]; //removing v1 from heap
        heapEnd--;
        swap(heap, 0, heapEnd);
        minHeapify(heap, heapEnd, 0, distance);
        if(distance[v1] == INF) break;

        EdgeNode* node = m_edges[v1];
        while(node){
            vertex v2 = node->vert;
            if(!visited[v2]){
                if (distance[v1] + node->weight < distance[v2]){
                    distance[v2] = distance[v1] + node->weight;
                    parents[v2] = v1;
                    heap[heapEnd++] = v2;
                    minHeapifyBottom(heap, heapEnd - 1, heapEnd, distance);
                }
            }
            node = node->next;
        }
        visited[v1] = true;
    }
}

//O(VE)
bool GraphAdjList::CPTBellmanFord(vertex v0, vertex parents[], int distance[]){
    const int INF = 2147483647 - 10000; //integer overflow may kill the algorithm
    for(vertex v = 0; v < m_numVertex; v++){
        parents[v] = -1;
        distance[v] = INF;
    }

    distance[v0] = 0;
    parents[v0] = v0;

    for(int i = 0; i < m_numVertex - 1; i++){
        for(int v1 = 0; v1 < m_numVertex; v1++){
            EdgeNode* node = m_edges[v1];
            while(node){
                vertex v2 = node->vert;
                if (distance[v1] + node->weight < distance[v2]){ //relaxing the edges
                    distance[v2] = distance[v1] + node->weight;
                    parents[v2] = v1;
                }
                node = node->next;
            }
        }
    }

    for(int v1 = 0; v1 < m_numVertex; v1++){
        EdgeNode* node = m_edges[v1];
        while(node){
            vertex v2 = node->vert;
            if (distance[v1] + node->weight < distance[v2]){ //relaxing the edges
                return false;
            }
            node = node->next;
        }
    }
    return true;
}

/*
int main(){
    GraphMatrix g1 = GraphMatrix(6);
    g1.addEdge(0, 1, 99);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(1, 4);
    g1.addEdge(2, 4);
    g1.addEdge(3, 4);
    g1.addEdge(4, 5);
    g1.addEdge(4, 1);
    g1.print();
    cout << endl;

    //WIP
    g1.removeEdge(4, 1);

    int distances[6];
    vertex parents[6];
    cout << "g1 topológico" << endl;
    g1.dagSPT(parents, distances);
    cout << endl << "Quais as menores distâncias possíveis para se chegar nos vértices, partindo do pai? (sem contar pesos)";
    printList(distances, 6);
    cout << "Qual a configuração da SPT? ";
    printList(parents, 6);

    g1.addEdge(4, 1);

    cout << "g1 não é mais topológico";
    g1.dagSPT(parents, distances);
    cout << endl << "Quais as menores distâncias possíveis para se chegar nos vértices, partindo do pai? ";
    printList(distances, 6);
    cout << "Qual a configuração da SPT? ";
    printList(parents, 6);

    GraphMatrix g2 = GraphMatrix(6);
    g2.addEdge(5, 0);
    g2.addEdge(5, 3);
    g2.addEdge(5, 4);
    g2.addEdge(4, 2);
    g2.addEdge(3, 0);
    g2.addEdge(3, 1);
    g2.addEdge(2, 0);
    g2.addEdge(2, 1);

    int topologicalOrdering[6];
    for(int i = 0; i < 6; i++){topologicalOrdering[i] = -1;}
    cout << endl << "g2 tem ordenação topológica? " << g2.hasTopologicalOrder(topologicalOrdering) << endl;
    printList(topologicalOrdering, 6);

    g2.dagSPT(parents, distances);
    cout << endl << "Em g2, quais as menores distâncias possíveis para se chegar nos vértices, partindo do pai? ";
    printList(distances, 6);
    cout << "Em g2, qual a configuração da SPT? ";
    printList(parents, 6);

    for(int i = 0; i < 6; i++){distances[i] = 0; parents[i] = 0;}
    g1.SPT(0, parents, distances);
    cout << endl << "Menores distâncias partindo de 0 em g1: ";
    printList(distances, 6);
    cout << "SPT: ";
    printList(parents, 6)

    for(int i = 0; i < 6; i++){distances[i] = 0; parents[i] = 0;}
    g1.SPT(4, parents, distances);
    cout << endl << "Menores distâncias partindo de 4 em g1: ";
    printList(distances, 6);
    cout << "SPT: ";
    printList(parents, 6)

    cout << endl;

    //http://graphonline.top/en/?graph=EBRQQOMYwjhUngCi
    GraphMatrix g3 = GraphMatrix(8);
    g3.addEdge(7, 1, 7);
    g3.addEdge(1, 2, 5);
    g3.addEdge(1, 5, 14);
    g3.addEdge(0, 4, 1);
    g3.addEdge(1, 4, 6);
    g3.addEdge(4, 1, 2);
    g3.addEdge(2, 7, 11);
    g3.addEdge(6, 5, 1);
    g3.addEdge(5, 6, 6);
    g3.addEdge(6, 0, 14);
    g3.addEdge(3, 1, 14);
    g3.addEdge(5, 1, 2);

    g3.print();

    vertex g3Parents[8];
    int g3Distances[8];
    g3.CPTDijkstra(0, g3Parents, g3Distances);
    cout << "Menores distâncias partindo de 0 em g3: ";
    printList(g3Distances, 8);
    cout << "CPT: ";
    printList(g3Parents, 8);

    cout << "Agora com BellmanFord" << endl;
    g3.CPTBellmanFord(0, g3Parents, g3Distances);
    cout << "Menores distâncias partindo de 0 em g3: ";
    printList(g3Distances, 8);
    cout << "CPT: ";
    printList(g3Parents, 8);

    //http://graphonline.top/en/?graph=VkYRfhrrjaiHYihj
    GraphMatrix g4 = GraphMatrix(9);
    g4.addEdge(1, 2, 5);
    g4.addEdge(1, 5, 14);
    g4.addEdge(0, 4, 1);
    g4.addEdge(1, 4, 6);
    g4.addEdge(2, 7, 11);
    g4.addEdge(5, 6, 6);
    g4.addEdge(6, 0, 14);
    g4.addEdge(3, 1, 14);
    g4.addEdge(8, 5, 5);
    g4.addEdge(5, 1, -4);
    g4.addEdge(7, 1, -4);
    g4.addEdge(6, 5, -3);
    g4.addEdge(2, 8, -2);
    g4.addEdge(4, 1, -1);

    g4.print();

    vertex g4Parents[9];
    int g4Distances[9];
    cout << endl << "BellmanFord deu certo em g4? ";
    cout << g4.CPTBellmanFord(3, g4Parents, g4Distances) << endl;
    cout << "Menores distâncias partindo de 0 em g4: ";
    printList(g4Distances, 9);
    cout << "CPT: ";
    printList(g4Parents, 9);

    g4.removeEdge(4, 1);
    g4.addEdge(4, 1, -7);

    cout << "Agora g8 tem ciclo negativo. ";
    cout << "BellmanFord deu certo em v8? ";
    cout << g4.CPTBellmanFord(3, g4Parents, g4Distances) << endl;
    cout << "Menores distâncias partindo de 0 em g8: ";
    printList(g4Distances, 9);
    cout << "CPT: ";
    printList(g4Parents, 9);

    cout << endl;
    cout << "!-- Agora para grafos feitos com listas de adjacência --!" << endl;
    cout << endl;

    //testing everything again but for adjacency list graphs

    GraphAdjList g5 = GraphAdjList(6);
    g5.addEdge(0, 1);
    g5.addEdge(0, 2);
    g5.addEdge(1, 3);
    g5.addEdge(1, 4);
    g5.addEdge(2, 4);
    g5.addEdge(3, 4);
    g5.addEdge(4, 5);
    g5.addEdge(4, 1);
    g5.print();
    cout << endl;

    g5.removeEdge(4, 1);

    cout << "g5 topológico" << endl;
    g5.dagSPT(parents, distances);
    cout << endl << "Quais as menores distâncias possíveis para se chegar nos vértices, partindo do pai? (sem contar pesos)";
    printList(distances, 6);
    cout << "Qual a configuração da SPT? ";
    printList(parents, 6);

    g5.addEdge(4, 1);

    cout << "g5 não é mais topológico";
    g5.dagSPT(parents, distances);
    cout << endl << "Quais as menores distâncias possíveis para se chegar nos vértices, partindo do pai? ";
    printList(distances, 6);
    cout << "Qual a configuração da SPT? ";
    printList(parents, 6);

    GraphAdjList g6 = GraphAdjList(6);
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

    g6.dagSPT(parents, distances);
    cout << endl << "Em g6, quais as menores distâncias possíveis para se chegar nos vértices, partindo do pai? ";
    printList(distances, 6);
    cout << "Em g6, qual a configuração da SPT? ";
    printList(parents, 6);

    for(int i = 0; i < 6; i++){distances[i] = 0; parents[i] = 0;}
    g5.SPT(0, parents, distances);
    cout << endl << "Menores distâncias partindo de 0 em g4: ";
    printList(distances, 6);
    cout << "SPT: ";
    printList(parents, 6)

    for(int i = 0; i < 6; i++){distances[i] = 0; parents[i] = 0;}
    g5.SPT(4, parents, distances);
    cout << endl << "Menores distâncias partindo de 4 em g4: ";
    printList(distances, 6);
    cout << "SPT: ";
    printList(parents, 6)

    cout << endl;

    //http://graphonline.top/en/?graph=EBRQQOMYwjhUngCi
    GraphAdjList g7 = GraphAdjList(8);
    g7.addEdge(7, 1, 7);
    g7.addEdge(1, 2, 5);
    g7.addEdge(1, 5, 14);
    g7.addEdge(0, 4, 1);
    g7.addEdge(1, 4, 6);
    g7.addEdge(4, 1, 2);
    g7.addEdge(2, 7, 11);
    g7.addEdge(6, 5, 1);
    g7.addEdge(5, 6, 6);
    g7.addEdge(6, 0, 14);
    g7.addEdge(3, 1, 14);
    g7.addEdge(5, 1, 2);


    g7.print();

    vertex g7Parents[8];
    int g7Distances[8];
    g7.CPTDijkstra(0, g7Parents, g7Distances);
    cout << "Menores distâncias partindo de 0 em g7: ";
    printList(g7Distances, 8);
    cout << "CPT: ";
    printList(g7Parents, 8);

    cout << "Agora com BellmanFord" << endl;
    g7.CPTBellmanFord(0, g7Parents, g7Distances);
    cout << "Menores distâncias partindo de 0 em g7: ";
    printList(g7Distances, 8);
    cout << "CPT: ";
    printList(g7Parents, 8);

    //http://graphonline.top/en/?graph=VkYRfhrrjaiHYihj
    GraphAdjList g8 = GraphAdjList(9);
    g8.addEdge(1, 2, 5);
    g8.addEdge(1, 5, 14);
    g8.addEdge(0, 4, 1);
    g8.addEdge(1, 4, 6);
    g8.addEdge(2, 7, 11);
    g8.addEdge(5, 6, 6);
    g8.addEdge(6, 0, 14);
    g8.addEdge(3, 1, 14);
    g8.addEdge(8, 5, 5);
    g8.addEdge(5, 1, -4);
    g8.addEdge(7, 1, -4);
    g8.addEdge(6, 5, -3);
    g8.addEdge(2, 8, -2);
    g8.addEdge(4, 1, -1);

    g8.print();

    vertex g8Parents[9];
    int g8Distances[9];
    cout << endl << "BellmanFord deu certo em v8? ";
    cout << g8.CPTBellmanFord(3, g8Parents, g8Distances) << endl;
    cout << "Menores distâncias partindo de 0 em g8: ";
    printList(g8Distances, 9);
    cout << "CPT: ";
    printList(g8Parents, 9);

    g8.removeEdge(4, 1);
    g8.addEdge(4, 1, -7);

    cout << "Agora g8 tem ciclo negativo. ";
    cout << "BellmanFord deu certo em v8? ";
    cout << g8.CPTBellmanFord(3, g8Parents, g8Distances) << endl;
    cout << "Menores distâncias partindo de 0 em g8: ";
    printList(g8Distances, 9);
    cout << "CPT: ";
    printList(g8Parents, 9);
}
*/
