# Hospital Emergency Triage Priority System
A hospital emergency department receives patients continuously. Each patient is assigned a triage priority score by the medical triage system. Patients with higher scores must be attended to before patients with lower scores.

The hospital uses an array-based Max-Heap to manage the emergency queue.

Each patient record contains: Patient ID, Patient name, Triage priority score

---

## Task 1: Build Max-Heap

### Initial Binary Tree
Before heapification, elements populate the zero-indexed array sequentially:
- Index 0: [PO1] Amina (72)
- Index 1: [PO2] Daniel (45)
- Index 2: [PO3] Eric (91)
- Index 3: [PO4] Grace (63)
- Index 4: [PO5] Hassan (88)
- Index 5: [PO6] Irene (54)
- Index 6: [PO7] Jean (76)

### Bottom-Up Heapify
We execute down-heapify starting from the last non-leaf node, index `(7 / 2) - 1 = 2`.
1. **Index 2 (Eric: 91):** Children are index 5 (54) and index 6 (76). 91 is greater than both. No change.
2. **Index 1 (Daniel: 45):** Children are index 3 (63) and index 4 (88). Largest child is 88. Swap Daniel (45) with Hassan (88).
3. **Index 0 (Amina: 72):** Children are index 1 (Hassan: 88) and index 2 (Eric: 91). Largest child is 91. Swap Amina (72) with Eric (91). Amina ripples down to index 2; its new children are index 5 (54) and index 6 (76). Swap Amina (72) with Jean (76).

### Final Heap Array Representation
- Index 0: [PO3] Eric (91)
- Index 1: [PO5] Hassan (88)
- Index 2: [PO7] Jean (76)
- Index 3: [PO4] Grace (63)
- Index 4: [PO2] Daniel (45)
- Index 5: [PO6] Irene (54)
- Index 6: [PO1] Amina (72)

---

## Task 2: Generate Treatment Order
Extracting maximum element (root node) repeatedly from a tracking copy yields patients in descending order without destroying the persistent storage state needed for subsequent modifications:
1. Patient PO3 — Eric — Priority 91
2. Patient PO5 — Hassan — Priority 88
3. Patient PO7 — Jean — Priority 76
4. Patient PO1 — Amina — Priority 72
5. Patient PO4 — Grace — Priority 63
6. Patient PO6 — Irene — Priority 54
7. Patient PO2 — Daniel — Priority 45

---

## Task 3: New Emergency Patient

### Insertion
1. `[P08] Kofi (98)` is added to the end of the array at Index 7.
2. **Up-Heapify (Bubble Up):**
   - Compare index 7 (98) with parent index 3 (Grace: 63) -> Swap.
   - Compare index 3 (98) with parent index 1 (Hassan: 88) -> Swap.
   - Compare index 1 (98) with parent index 0 (Eric: 91) -> Swap.

### Final Heap Array Representation
- Index 0: [P08] Kofi (98)
- Index 1: [PO3] Eric (91)
- Index 2: [PO7] Jean (76)
- Index 3: [PO5] Hassan (88)
- Index 4: [PO2] Daniel (45)
- Index 5: [PO6] Irene (54)
- Index 6: [PO1] Amina (72)
- Index 7: [PO4] Grace (63)

---

## Task 4: Patient Cleared

### Removal
1. Locate `P08` via ID lookup (found at root index 0).
2. Replace it with last element in the array `[PO4] Grace (63)` and decrement the heap size tracker.
3. Run `heapify` down from root index 0 to preserve structural requirements.
   - Compare index 0 (63) with children index 1 (91) and index 2 (76). Swap with 91.
   - Compare index 1 (63) with children index 3 (88) and index 4 (45). Swap with 88.
4. Node `PO4:63` settles at index 3.

### Final Heap Array Representation
- Index 0: [PO3] Eric (91)
- Index 1: [PO5] Hassan (88)
- Index 2: [PO7] Jean (76)
- Index 3: [PO4] Grace (63)
- Index 4: [PO2] Daniel (45)
- Index 5: [PO6] Irene (54)
- Index 6: [PO1] Amina (72)

