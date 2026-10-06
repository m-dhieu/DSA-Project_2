#include <stdio.h>

#define INF 1000000000
#define MAX_VERTICES 26

/* directed, weighted data-transfer route */
typedef struct {
    char from;
    char to;
    int weight;
} Edge;

/* map data-center char label to an array index & back */
int charToIndex(char c) {
    if (c >= 'A' && c <= 'Z')
        return c - 'A';

    return -1;
}

char indexToChar(int index) {
    return (char)(index + 'A');
}

/* print shortest path */
void printPath(int parent[], int vertex) {
    if (parent[vertex] == -1) {
        printf("%c", indexToChar(vertex));
        return;
    }

    printPath(parent, parent[vertex]);
    printf(" -> %c", indexToChar(vertex));
}

void bellmanFord(Edge edges[], int edgeCount, char sourceChar) {
    int dist[MAX_VERTICES];
    int parent[MAX_VERTICES];
    int present[MAX_VERTICES] = {0};
    int vertexCount = 0;

    /* identify data centers present */
    for (int i = 0; i < edgeCount; i++) {
        int u = charToIndex(edges[i].from);
        int v = charToIndex(edges[i].to);

        if (u == -1 || v == -1)
            continue;

        present[u] = 1;
        present[v] = 1;
    }

    for (int i = 0; i < MAX_VERTICES; i++) {
        if (present[i])
            vertexCount++;
    }

    int src = charToIndex(sourceChar);

    if (src == -1 || !present[src]) {
        printf("Error: Data center '%c' doesn't exist in network.\n",
               sourceChar);
        return;
    }

    for (int i = 0; i < MAX_VERTICES; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[src] = 0;

    /* Bellman-Ford relaxation: V - 1 iterations */
    for (int i = 1; i <= vertexCount - 1; i++) {
        for (int j = 0; j < edgeCount; j++) {
            int u = charToIndex(edges[j].from);
            int v = charToIndex(edges[j].to);
            int weight = edges[j].weight;

            if (u == -1 || v == -1)
                continue;

            /* only relax edges from reachable vertices */
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    /* check for -ve weight cycle reachable from source */
    int hasNegativeCycle = 0;

    for (int j = 0; j < edgeCount; j++) {
        int u = charToIndex(edges[j].from);
        int v = charToIndex(edges[j].to);
        int weight = edges[j].weight;

        if (u == -1 || v == -1)
            continue;

        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            hasNegativeCycle = 1;
            break;
        }
    }

    printf("\nNegative-Weight Cycle Detection *_*\n");

    if (hasNegativeCycle) {
        printf("Negative-weight cycle detected.\n");
        printf("Shortest-path results may be undefined.\n");
        return;
    }

    printf("No negative-weight cycle detected.\n");

    /* display routing table */
    printf("\nSource: %c\n", sourceChar);
    printf("%-12s %-15s %s\n",
           "Destination", "Shortest Cost", "Path");

    for (int i = 0; i < MAX_VERTICES; i++) {
        if (present[i] && i != src) {
            printf("%-12c ", indexToChar(i));

            if (dist[i] == INF) {
                printf("%-15s %s\n", "INF", "Unreachable");
            } else {
                printf("%-15d ", dist[i]);
                printPath(parent, i);
                printf("\n");
            }
        }
    }
}

int main(void) {
    /* weighted directed graph repping data-center network */
    Edge networkEdges[] = {
        {'A', 'B', 6},
        {'A', 'D', 16},
        {'B', 'C', 6},
        {'B', 'D', 6},
        {'B', 'J', 7},
        {'C', 'G', -9},
        {'D', 'E', 7},
        {'D', 'J', 8},
        {'E', 'F', 10},
        {'E', 'I', -2},
        {'F', 'G', 4},
        {'F', 'I', 2},
        {'G', 'H', 13},
        {'I', 'F', 2},
        {'J', 'E', 3}
    };

    int edgeCount = sizeof(networkEdges) / sizeof(networkEdges[0]);
    char inputChar;

    printf("Enter starting data center (A-J): ");

    if (scanf(" %c", &inputChar) != 1) {
        printf("Error: Invalid input.\n");
        return 1;
    }

    bellmanFord(networkEdges, edgeCount, inputChar);

    return 0;
}

