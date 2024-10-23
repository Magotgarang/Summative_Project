#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct EdgeNode {
    int vertex;
    int weight;
    struct EdgeNode* next;
} EdgeNode;

typedef struct {
    int vertices;
    EdgeNode* adjList[MAX];
} Graph;

// Function to create an adjacency list
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Function to add edge to the graph
void addEdge(Graph* graph, int u, int v, int weight) {
    EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = graph->adjList[u];
    graph->adjList[u] = newNode;

    // If the graph is undirected, add an edge from v to u as well
    newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    newNode->vertex = u;
    newNode->weight = weight;
    newNode->next = graph->adjList[v];
    graph->adjList[v] = newNode;
}

// Function to find the vertex with minimum distance value
int minDistance(int dist[], int sptSet[], int vertices) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Dijkstra's algorithm for shortest path
void dijkstra(Graph* graph, int src) {
    int dist[MAX], sptSet[MAX];

    for (int i = 0; i < graph->vertices; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < graph->vertices - 1; count++) {
        int u = minDistance(dist, sptSet, graph->vertices);
        sptSet[u] = 1;

        EdgeNode* temp = graph->adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            if (sptSet[v] == 0 && 
                dist[u] != INT_MAX && 
                dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
            }
            temp = temp->next;
        }
    }

    printf("Vertex Distance from Source %d\n", src);
    for (int i = 0; i < graph->vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Bellman-Ford algorithm to find the shortest path
void bellmanFord(Graph* graph, int src) {
    int dist[MAX];

    for (int i = 0; i < graph->vertices; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for (int i = 1; i <= graph->vertices - 1; i++) {
        for (int u = 0; u < graph->vertices; u++) {
            EdgeNode* temp = graph->adjList[u];
            while (temp != NULL) {
                if (dist[u] != INT_MAX && 
                    dist[u] + temp->weight < dist[temp->vertex]) {
                    dist[temp->vertex] = dist[u] + temp->weight;
                }
                temp = temp->next;
            }
        }
    }

    printf("Vertex Distance from Source %d\n", src);
    for (int i = 0; i < graph->vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Function to input the graph
void inputGraph(Graph* graph) {
    int edges, u, v, weight;

    printf("Enter number of vertices: ");
    scanf("%d", &graph->vertices);
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v weight): ");
        scanf("%d %d %d", &u, &v, &weight);
        addEdge(graph, u, v, weight);
    }
}

int main() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    int src, choice;

    inputGraph(graph);
    printf("Enter source vertex for Dijkstra: ");
    scanf("%d", &src);
    printf("1. Dijkstra's Algorithm\n2. Bellman-Ford Algorithm\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            dijkstra(graph, src);
            break;
        case 2:
            bellmanFord(graph, src);
            break;
        default:
            printf("Invalid choice.\n");
    }

    // Free memory
    for (int i = 0; i < graph->vertices; i++) {
        EdgeNode* temp = graph->adjList[i];
        while (temp) {
            EdgeNode* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph);

    return 0;
}
