#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    char phone[15];
} Person;

typedef struct {
    int adj[MAX][MAX];
    int visited[MAX];
    Person persons[MAX];
    int numPersons;
} Graph;

void initGraph(Graph* g, int num) {
    g->numPersons = num;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            g->adj[i][j] = 0;
        }
    }
}

void addEdge(Graph* g, int src, int dest) {
    g->adj[src][dest] = 1;
    g->adj[dest][src] = 1; // Undirected graph
}

void addPerson(Graph* g, int index, const char* name, const char* phone) {
    strcpy(g->persons[index].name, name);
    strcpy(g->persons[index].phone, phone);
}

void dfs(Graph* g, int v) {
    g->visited[v] = 1;
    printf("%s (%s)\n", g->persons[v].name, g->persons[v].phone);

    for (int i = 0; i < g->numPersons; i++) {
        if (g->adj[v][i] && !g->visited[i]) {
            dfs(g, i);
        }
    }
}

void trackCriminals(Graph* g) {
    printf("Tracking contacts:\n");
    for (int i = 0; i < g->numPersons; i++) {
        if (!g->visited[i]) {
            dfs(g, i);
        }
    }
}

int main() {
    Graph g;
    int numPersons;

    printf("Enter number of persons: ");
    scanf("%d", &numPersons);
    initGraph(&g, numPersons);

    for (int i = 0; i < numPersons; i++) {
        char name[50], phone[15];
        printf("Enter name and phone for person %d: ", i + 1);
        scanf("%s %s", name, phone);
        addPerson(&g, i, name, phone);
    }

    printf("Enter number of connections: ");
    int connections;
    scanf("%d", &connections);

    for (int i = 0; i < connections; i++) {
        int src, dest;
        printf("Enter connection (src dest): ");
        scanf("%d %d", &src, &dest);
        addEdge(&g, src, dest);
    }

    trackCriminals(&g);
    return 0;
}

