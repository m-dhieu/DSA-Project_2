#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char id[10];       
    char name[50];     
    int priority;
} Patient;

void swap(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

/* restore max-heap downwards */
void heapify(Patient heap[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].priority > heap[largest].priority)
        largest = left;

    if (right < size && heap[right].priority > heap[largest].priority)
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapify(heap, size, largest);
    }
}

/* convert array into Max-Heap */
void buildMaxHeap(Patient heap[], int size) {
    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapify(heap, size, i);
    }
}

/* restore max-heap upwards */
void upHeapify(Patient heap[], int i) {
    while (i > 0 && heap[(i - 1) / 2].priority < heap[i].priority) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/* insert item */
void insert(Patient heap[], int *size, Patient newPatient) {
    if (*size >= MAX_SIZE) {
        printf("Error: Heap overflow!\n");
        return;
    }
    heap[*size] = newPatient;
    (*size)++;
    upHeapify(heap, *size - 1);
}

/* remove & extract max value */
Patient extractMax(Patient heap[], int *size) {
    Patient maxPatient = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify(heap, *size, 0);
    return maxPatient;
}

/* delete by key */
void deletePatientByID(Patient heap[], int *size, const char *id) {
    int targetIndex = -1;
    
    for (int i = 0; i < *size; i++) {
        if (strcmp(heap[i].id, id) == 0) {
            targetIndex = i;
            break;
        }
    }
    
    if (targetIndex == -1) {
        printf("Patient with ID %s not found.\n", id);
        return;
    }
    
    heap[targetIndex] = heap[*size - 1];
    (*size)--;
    
    if (targetIndex < *size) {
        if (targetIndex > 0) {
            int parentIndex = (targetIndex - 1) / 2;
            if (heap[targetIndex].priority > heap[parentIndex].priority) {
                upHeapify(heap, targetIndex);
                return;
            }
        }
        heapify(heap, *size, targetIndex);
    }
}

void printHeap(Patient heap[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Index %d: [%s] %s (Priority: %d)\n", i, heap[i].id, heap[i].name, heap[i].priority);
    }
    printf("\n");
}

int main(void) {
    Patient queue[MAX_SIZE] = {
        {"PO1", "Amina", 72},
        {"PO2", "Daniel", 45},
        {"PO3", "Eric", 91},
        {"PO4", "Grace", 63},
        {"PO5", "Hassan", 88},
        {"PO6", "Irene", 54},
        {"PO7", "Jean", 76}
    };
    int size = 7;

    printf("Initial Max-Heap :)\n");
    buildMaxHeap(queue, size);
    printHeap(queue, size);

    printf("Treatment Order:\n");
    Patient tempQueue[MAX_SIZE];
    int tempSize = size;
    memcpy(tempQueue, queue, sizeof(Patient) * size);
    while (tempSize > 0) {
        Patient p = extractMax(tempQueue, &tempSize);
        printf("Patient %s — %s — Priority %d\n", p.id, p.name, p.priority);
    }
    printf("\n");

    printf("After Inserting Kofi (P08)...\n");
    Patient kofi = {"P08", "Kofi", 98};
    insert(queue, &size, kofi);
    printHeap(queue, size);

    printf("After Removing Kofi (P08)...\n");
    deletePatientByID(queue, &size, "P08");
    printHeap(queue, size);

    return 0;
}

