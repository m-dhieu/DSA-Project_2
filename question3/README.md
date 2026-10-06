# EV Charging Station Power Network
A city is installing a network of electric vehicle (EV) charging stations. The charging stations must be connected to the city's main power distribution network so that every station can receive electricity either directly or through another station.

Several possible underground power-cable connections are available. Each connection has an estimated installation cost.

The network is modeled as an undirected weighted graph.

---

## Task 1: Graph Representation (Adjacency Matrix)
The network is modeled as an undirected, weighted graph with 7 vertices (A through G):
* Rows and columns represent charging stations in alphabetical order.
* A value of 0 explicitly denotes no direct underground power-cable connection.
* The matrix is completely symmetric across the main diagonal, representing an undirected graph.

     A    B    C    D    E    F    G
A    0    6    0   12    0    0    0
B    6    0   11    5    0    0    0
C    0   11    0   17    0    0   25
D   12    5   17    0   22   15    0
E    0    0    0   22    0   10    0
F    0    0    0   15   10    0   22
G    0    0   25    0    0   22    0

---

## Task 2: Apply Kruskal's Algorithm

### Sort Connections by Increasing Cost
1. B — D : 5
2. A — B : 6
3. E — F : 10
4. B — C : 11
5. A — D : 12
6. D — F : 15
7. C — D : 17
8. D — E : 22
9. F — G : 22
10. C — G : 25

### Connection Evaluation Sequence
We sequentially evaluate edges from the sorted list, adding them to our Minimum Spanning Tree (MST) only if they connect distinct components without creating a cycle.

1. **Evaluate B — D : 5**
   * Status: **Selected**
   * Why: Connects separate components {B} and {D}. No cycle formed.
2. **Evaluate A — B : 6**
   * Status: **Selected**
   * Why: Connects separate components {A} and {B, D}. No cycle formed.
3. **Evaluate E — F : 10**
   * Status: **Selected**
   * Why: Connects separate components {E} and {F}. No cycle formed.
4. **Evaluate B — C : 11**
   * Status: **Selected**
   * Why: Connects separate components {C} and {A, B, D}. No cycle formed.
5. **Evaluate A — D : 12**
   * Status: *Rejected*
   * Why: Stations A and D are reachable via path A — B — D. Including this edge forms the cycle `A—B—D—A`.
6. **Evaluate D — F : 15**
   * Status: **Selected**
   * Why: Merges component {A, B, C, D} with component {E, F}. No cycle formed.
7. **Evaluate C — D : 17**
   * Status: *Rejected*
   * Why: Stations C and D are reachable via path C — B — D. Including this edge forms the cycle `C—B—D—C`.
8. **Evaluate D — E : 22**
   * Status: *Rejected*
   * Why: Stations D and E are reachable via path D — F — E. Including this edge forms the cycle `D—F—E—D`.
9. **Evaluate F — G : 22**
   * Status: **Selected**
   * Why: Connects the final isolated station {G} to the main component. No cycle formed.

*Termination Criteria Met:* Exactly V - 1 = 6 edges have been successfully selected to connect all 7 stations. Remaining edges are skipped.

---

## Task 3: Identify Selected Connections
The following cable connections establish a valid MST that spans all stations without closed loops, meeting minimum possible weight:

Selected Connections:
B — D : 5
A — B : 6
E — F : 10
B — C : 11
D — F : 15
F — G : 22

---

## Task 4: Calculate Total Installation Cost
Total Installation Cost: **69** thousand dollars
*(Found mathematically as: 5 + 6 + 10 + 11 + 15 + 22 = 69)*

