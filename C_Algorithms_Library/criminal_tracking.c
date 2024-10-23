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

// Initialize the graph
void initGraph(Graph* g, int num) {
    g->numPersons = num;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            g->adj[i][j] = 0;
        }
        g->visited[i] = 0; // Initialize visited array
    }
}

// Add an edge to the graph
void addEdge(Graph* g, int src, int dest) {
    g->adj[src][dest] = 1;
    g->adj[dest][src] = 1; // Undirected graph
}

// Add a person to the graph
void addPerson(Graph* g, int index, const char* name, const char* phone) {
    strcpy(g->persons[index].name, name);
    strcpy(g->persons[index].phone, phone);
}

// BFS function to track contacts
void bfs(Graph* g, int start) {
    int queue[MAX], front = 0, rear = 0;
    int level[MAX]; // To track levels
    g->visited[start] = 1;
    queue[rear++] = start;
    level[start] = 0; // Start level

    printf("Tracking contacts from criminal %s (%s):\n", g->persons[start].name, g->persons[start].phone);

    while (front < rear) {
        int current = queue[front++];
        printf("Level %d: %s (%s)\n", level[current], g->persons[current].name, g->persons[current].phone);

        for (int i = 0; i < g->numPersons; i++) {
            if (g->adj[current][i] && !g->visited[i]) {
                g->visited[i] = 1;
                queue[rear++] = i;
                level[i] = level[current] + 1; // Set level for next contacts
            }
        }
    }
}

// Function to initiate tracking from the criminal
void trackCriminals(Graph* g, int criminalIndex) {
    bfs(g, criminalIndex);
}

int main() {
    Graph g;
    int numPersons;

    printf("Enter number of persons: ");
    scanf("%d", &numPersons);
    initGraph(&g, numPersons);

    for (int i = 0; i < numPersons; i++) {
        char input[65];
        printf("Enter phone and name for person %d (e.g., +25078654759 David): ", i + 1);
        scanf(" %[^\n]", input); // Read a whole line of input

        char *phone = strtok(input, " "); // Get the first token (phone number)
        char *name = strtok(NULL, "\n"); // Get the remaining string (name)

        if (phone && name) {
            addPerson(&g, i, name, phone);
        } else {
            printf("Invalid input. Please enter both phone and name.\n");
            i--; // Decrement to retry this person
        }
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

    // Allow user to select the source node (criminal)
    int criminalIndex;
    printf("Enter the index of the criminal (0 to %d): ", numPersons - 1);
    scanf("%d", &criminalIndex);
    
    trackCriminals(&g, criminalIndex);

    return 0;
}
