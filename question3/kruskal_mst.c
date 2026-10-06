#include <stdio.h>
#include <stdlib.h>

#define V 7
#define E 10

/* undirected, weighted edge */
struct Edge {
    char src, dest;
    int weight;
};

/* union-find subset node */
struct Subset {
    int parent;
    int rank;
};

/* ascending order */
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    /* attach lower tree under higher */
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        /* if same, make one root & increment its rank */
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int main(void) {
    /* adjacency matrix representation (A=0, B=1, C=2, D=3, E=4, F=5, G=6) */
    int adjMatrix[V][V] = {
        {0,  6,  0, 12,  0,  0,  0}, /* row A */
        {6,  0, 11,  5,  0,  0,  0}, /* B */
        {0, 11,  0, 17,  0,  0, 25}, /* C */
        {12, 5, 17,  0, 22, 15,  0}, /* D */
        {0,  0,  0, 22,  0, 10,  0}, /* E */
        {0,  0,  0, 15, 10,  0, 22}, /* F */
        {0,  0, 25,  0,  0, 22,  0}  /* G */
    };

    /* parse upper triangle to populate edge arrays */
    struct Edge edges[E];
    int edgeCount = 0;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (adjMatrix[i][j] != 0) {
                edges[edgeCount].src = 'A' + i;
                edges[edgeCount].dest = 'A' + j;
                edges[edgeCount].weight = adjMatrix[i][j];
                edgeCount++;
            }
        }
    }

    /* Kruskal sorting */
    qsort(edges, E, sizeof(struct Edge), compareEdges);

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    if (subsets == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    struct Edge result[V - 1]; /* holds output configs */
    int e = 0; /* tracks accepted edges */
    int i = 0; /* tracks evaluation steps */

    while (e < V - 1 && i < E) {
        struct Edge next_edge = edges[i++];
        int x = find(subsets, next_edge.src - 'A');
        int y = find(subsets, next_edge.dest - 'A');
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    /* output format */
    printf("Selected Connections:\n");
    int total_cost = 0;
    for (i = 0; i < e; ++i) {
        printf("%c — %c : %d\n", result[i].src, result[i].dest, result[i].weight);
        total_cost += result[i].weight;
    }
    
    printf("Total Installation Cost: %d thousand dollars\n", total_cost);

    free(subsets);
    return 0;
}

