# Airport Baggage Handling Priority Queue
At an international airport, an automated baggage handling system assigns a priority score to baggage containers based on factors such as connecting-flight departure time, passenger priority, and handling requirements.

The system must always process the container with the highest priority score first. An array-based Max-Heap is used to efficiently manage the containers.

The following priority scores have been received:

P = {56, 23, 91, 34, 72, 48, 85, 17, 63, 79, 42}

---

## Task 1: Build Max-Heap

### Map Containers to Priorities
Containers are assigned unique identifiers sequentially based on receipt order:
* **A:** 56, **B:** 23, **C:** 91, **D:** 34, **E:** 72, **F:** 48, **G:** 85, **H:** 17, **I:** 63, **J:** 79, **K:** 42

### Unsorted Tree (Initial Array)
Before heapification, the array matches the level-order input sequence:
`[(A, 56), (B, 23), (C, 91), (D, 34), (E, 72), (F, 48), (G, 85), (H, 17), (I, 63), (J, 79), (K, 42)]`

```
               A:56
             /      \
         B:23        C:91
        /    \       /   \
     D:34    E:72  F:48  G:85
     /  \    /  \
   H:17 I:63 J:79 K:42
```

### Bottom-Up Heapify
We run `heapifyDown` beginning from the last non-leaf node index \(\lfloor 11/2 \rfloor - 1 = 4\) down to index 0:
* **Index 4 (E:72):** Children are J:79 and K:42. Swap E and J.
* **Index 3 (D:34):** Children are H:17 and I:63. Swap D and I.
* **Index 2 (C:91):** Children are F:48 and G:85. Already valid (91 > 48, 85). No swap.
* **Index 1 (B:23):** Children are I:63 and J:79. Swap B and J. Then cascade down index 4: swap B(23) with child E(72).
* **Index 0 (A:56):** Children are J:79 and C:91. Swap A and C. Then cascade down index 2: swap A(56) with child G(85).

### Final Max-Heap
```
               C:91
             /      \
         J:79        G:85
        /    \       /   \
     I:63    E:72  F:48  A:56
     /  \    /  \
   H:17 D:34 B:23 K:42
```
* **Memory Array Layout:** `[(C, 91), (J, 79), (G, 85), (I, 63), (E, 72), (F, 48), (A, 56), (H, 17), (D, 34), (B, 23), (K, 42)]`

---

## Task 2: Urgent Baggage Container Insertion

### Upward Heapification
* **Step 1:** Add container `X:100` to index 11 (the left child of `F:48`).
* **Step 2:** Compare `X:100` with its parent `F:48` (index 5). Since 100 > 48, swap.
* **Step 3:** Compare `X:100` with its new parent `G:85` (index 2). Since 100 > 85, swap.
* **Step 4:** Compare `X:100` with root parent `C:91` (index 0). Since 100 > 91, swap. `X:100` becomes the root.

### Resulting Heap
```
               X:100
             /       \
         J:79         C:91
        /    \        /   \
     I:63    E:72   G:85  A:56
     /  \    /  \   /
   H:17 D:34 B:23 K:42 F:48
```
* **Memory Array Layout:** `[(X, 100), (J, 79), (C, 91), (I, 63), (E, 72), (G, 85), (A, 56), (H, 17), (D, 34), (B, 23), (K, 42), (F, 48)]`

---

## Task 3: Cancelled Container Removal

### Downward Re-Heapification
* **Step 1:** Search finds container `X` at root index 0. Replace index 0 with last leaf element `F:48`. Decrease heap size to 11.
* **Step 2:** Run `heapifyDown` at index 0. The children are `J:79` and `C:91`. The largest child is `C:91`. Swap `F:48` with `C:91`.
* **Step 3:** Run `heapifyDown` at index 2. The children are `G:85` and `A:56`. The largest child is `G:85`. Swap `F:48` with `G:85`.
* **Step 4:** Index 5 has no children within the new boundary size of 11. The heap structure is restored. Simplu, `F:48` is now at index 2. Its children are `G:85` at index 5 and `A:56` at index 6. Since `G:85` is greater than `F:48`, we swap them. `F:48` moves to index 5. At index 5, its left child would be index 11, which is outside the updated heap boundary (size = 11), so heapification terminates.

### Resulting Heap
```
               C:91
             /      \
         J:79        G:85
        /    \       /   \
     I:63    E:72  F:48  A:56
     /  \    /  \
   H:17 D:34 B:23 K:42
```
* **Memory Array Layout:** `[(C, 91), (J, 79), (G, 85), (I, 63), (E, 72), (F, 48), (A, 56), (H, 17), (D, 34), (B, 23), (K, 42)]`

