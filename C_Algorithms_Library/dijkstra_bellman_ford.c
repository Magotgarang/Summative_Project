#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    int vertices;
    int edges;
    Edge edge[MAX];
} Graph;

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
void dijkstra(Graph *graph, int src) {
    int dist[MAX], sptSet[MAX];

    for (int i = 0; i < graph->vertices; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < graph->vertices - 1; count++) {
        int u = minDistance(dist, sptSet, graph->vertices);
        sptSet[u] = 1;

        for (int j = 0; j < graph->edges; j++) {
            if (graph->edge[j].u == u && sptSet[graph->edge[j].v] == 0 && 
                dist[u] != INT_MAX && 
                dist[u] + graph->edge[j].weight < dist[graph->edge[j].v]) {
                dist[graph->edge[j].v] = dist[u] + graph->edge[j].weight;
            }
        }
    }

    printf("Vertex Distance from Source %d\n", src);
    for (int i = 0; i < graph->vertices; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Bellman-Ford algorithm to find the shortest path
void bellmanFord(Graph *graph, int src) {
    int dist[MAX];

    for (int i = 0; i < graph->vertices; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= graph->vertices - 1; i++) {
        for (int j = 0; j < graph->edges; j++) {
            if (dist[graph->edge[j].u] != INT_MAX && 
                dist[graph->edge[j].u] + graph->edge[j].weight < dist[graph->edge[j].v]) {
                dist[graph->edge[j].v] = dist[graph->edge[j].u] + graph->edge[j].weight;
            }
        }
    }

    printf("Vertex Distance from Source %d\n", src);
    for (int i = 0; i < graph->vertices; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Function to input the graph
void inputGraph(Graph *graph) {
    printf("Enter number of vertices: ");
    scanf("%d", &graph->vertices);
    printf("Enter number of edges: ");
    scanf("%d", &graph->edges);

    for (int i = 0; i < graph->edges; i++) {
        printf("Enter edge (u v weight): ");
        scanf("%d %d %d", &graph->edge[i].u, &graph->edge[i].v, &graph->edge[i].weight);
    }
}

int main() {
    Graph graph;
    int src, choice;

    inputGraph(&graph);
    printf("Enter source vertex for Dijkstra: ");
    scanf("%d", &src);
    printf("1. Dijkstra's Algorithm\n2. Bellman-Ford Algorithm\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            dijkstra(&graph, src);
            break;
        case 2:
            bellmanFord(&graph, src);
            break;
        default:
            printf("Invalid choice.\n");
    }
    return 0;
}
