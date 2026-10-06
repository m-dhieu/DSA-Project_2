#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 20

typedef struct {
    char id;
    int priority;
} Container;

typedef struct {
    Container data[MAX_CAPACITY];
    int size;
} MaxHeap;

void swap(Container *x, Container *y) {
    Container temp = *x;
    *x = *y;
    *y = temp;
}

void heapifyUp(MaxHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[index].priority > heap->data[parent].priority) {
            swap(&heap->data[index], &heap->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(MaxHeap *heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left].priority > heap->data[largest].priority) {
        largest = left;
    }
    if (right < heap->size && heap->data[right].priority > heap->data[largest].priority) {
        largest = right;
    }
    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        heapifyDown(heap, largest);
    }
}

void buildMaxHeap(MaxHeap *heap) {
    for (int i = (heap->size / 2) - 1; i >= 0; i--) {
        heapifyDown(heap, i);
    }
}

void insertContainer(MaxHeap *heap, char id, int priority) {
    if (heap->size >= MAX_CAPACITY) return;
    heap->data[heap->size].id = id;
    heap->data[heap->size].priority = priority;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

void removeContainerByID(MaxHeap *heap, char targetId) {
    int targetIndex = -1;
    for (int i = 0; i < heap->size; i++) {
        if (heap->data[i].id == targetId) {
            targetIndex = i;
            break;
        }
    }
    
    if (targetIndex == -1) return;

    /* replace target node with last element */
    heap->data[targetIndex] = heap->data[heap->size - 1];
    heap->size--;

    /* re-heapify only if element was not last item removed */
    if (targetIndex < heap->size) {
        if (targetIndex > 0) {
            int parentIndex = (targetIndex - 1) / 2;
            if (heap->data[targetIndex].priority > heap->data[parentIndex].priority) {
                heapifyUp(heap, targetIndex);
                return;
            }
        }
        /* if it can't move up, see if it needs to move down */
        heapifyDown(heap, targetIndex);
    }
}

void printHeapArray(const MaxHeap *heap) {
    printf("[");
    for (int i = 0; i < heap->size; i++) {
        printf("(%c, %d)", heap->data[i].id, heap->data[i].priority);
        if (i < heap->size - 1) printf(", ");
    }
    printf("]\n\n");
}

int main(void) {
    MaxHeap heap;
    heap.size = 11;
    
    char ids[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
    int priorities[] = {56, 23, 91, 34, 72, 48, 85, 17, 63, 79, 42};
    
    for (int i = 0; i < 11; i++) {
        heap.data[i].id = ids[i];
        heap.data[i].priority = priorities[i];
    }

    printf("Initial Max-Heap Construction :)\n");
    buildMaxHeap(&heap);
    printHeapArray(&heap);

    printf("Inserting Priority Container X (100)\n");
    insertContainer(&heap, 'X', 100);
    printHeapArray(&heap);

    printf("Removing Cancelled Container X\n");
    removeContainerByID(&heap, 'X');
    printHeapArray(&heap);

    return 0;
}

