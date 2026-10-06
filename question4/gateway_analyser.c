#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 7
#define NO_EDGE 0

/* map gateway char to matrix index and back */
int getIndex(char c) {
    if (c >= 'A' && c <= 'G') {
        return c - 'A';
    }
    return -1;
}

char getChar(int index) {
    return (char)('A' + index);
}

/* queue for BFS */
typedef struct {
    int items[MAX_NODES];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_NODES - 1) return;
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

int main(void) {
    /* adjacency matrix representation (A=0, B=1, C=2, D=3, E=4, F=5, G=6) */
    int graph[MAX_NODES][MAX_NODES] = {
        { 0,  6,  0, 12,  0,  0,  0}, /* row A */
        { 6,  0, 11,  5,  0,  0,  0}, /* B */
        { 0, 11,  0, 17,  0,  0, 25}, /* C */
        {12,  5, 17,  0, 22, 15,  0}, /* D */
        { 0,  0,  0, 22,  0, 10,  0}, /* E */
        { 0,  0,  0, 15, 10,  0, 22}, /* F */
        { 0,  0, 25,  0,  0, 22,  0}  /* G */
    };

    /* gateway selection */
    char startChar;
    printf("Enter starting gateway (A-G): ");
    if (scanf(" %c", &startChar) != 1) {
        return 1;
    }

    int startNode = getIndex(startChar);
    if (startNode == -1) {
        printf("Error: Gateway '%c' doesn't exist in network.\n", startChar);
        return 0;
    }

    /* BFS connectivity analysis */
    bool visited[MAX_NODES] = {false};
    Queue q;
    initQueue(&q);

    int directConnections[MAX_NODES];
    int directCount = 0;
    visited[startNode] = true;
    enqueue(&q, startNode);

    while (!isEmpty(&q)) {
        int currentNode = dequeue(&q);

        /* add adjacent nodes in alphabetical order (A to G) */
        for (int i = 0; i < MAX_NODES; i++) {
            if (graph[currentNode][i] != NO_EDGE && !visited[i]) {
                visited[i] = true;
                enqueue(&q, i);
                
                if (currentNode == startNode) {
                    directConnections[directCount++] = i;
                }
            }
        }
    }

    printf("One-hop neighbors of %c: ", startChar);
    for (int i = 0; i < directCount; i++) {
        printf("%c ", getChar(directConnections[i]));
    }
    printf("\n");

    /* communication analysis */
    int maxTime = -1;
    int maxNodeIndex = -1;

    /* scan only direct connections to eval edge weights */
    for (int i = 0; i < directCount; i++) {
        int neighborIdx = directConnections[i];
        int transferTime = graph[startNode][neighborIdx];
        if (transferTime > maxTime) {
            maxTime = transferTime;
            maxNodeIndex = neighborIdx;
        }
    }

    if (maxNodeIndex != -1) {
        printf("Highest-transfer-time neighbor: %c (%d ms)\n", 
               getChar(maxNodeIndex), maxTime);
    } else {
        printf("No connections found.\n");
    }

    return 0;
}

