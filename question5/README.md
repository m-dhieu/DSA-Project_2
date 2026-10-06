# Cloud Service Data Routing Analyser
A company operates several data centers that exchange application data and backups. A routing analyzer is used to determine the minimum cumulative cost of sending data from the Primary Data Center (A) to every other data center.

The network is modeled as a weighted directed graph:

- Each node represents a data center.
- Each directed edge represents a possible data-transfer route.
- Each edge weight represents the net transfer cost of using that route.
- A negative weight represents a route that provides a transfer credit or optimization benefit that reduces the overall cost.

---

## Graph Representation
The cloud routing infrastructure is modeled as a Weighted Directed Graph G = (V, E) where:
- **Vertices (V):** Active data centers mapped dynamically as character keys `[A, B, C, D, E, F, G, H, I, J]`.
- **Edges (E):** Data-transfer routes pointing sequentially from a source vertex to a destination vertex.
- **Weights (W):** Net transfer costs associated with a directed path. Negative weights accurately mirror optimization credits applied to specific hardware routes.

---

## Analytical Verification & Execution Trace

### Network Optimization Trace Equations
- **Node B (Cost 6):** Direct evaluation from Source via A → B.
- **Node C (Cost 12):** Evaluates optimally via A → B → C = 6 + 6 = 12.
- **Node D (Cost 12):** Bypasses the direct A → D path (cost 16) by evaluating the relaxation via B: \(Cost(B) + Cost(B \rightarrow D) = 6 + 6 = 12\).
- **Node J (Cost 13):** Bypasses D and runs via B: \(Cost(B) + Cost(B \rightarrow J) = 6 + 7 = 13\).
- **Node E (Cost 16):** Evaluates via J: \(Cost(J) + Cost(J \rightarrow E) = 13 + 3 = 16\).
- **Node I (Cost 14):** Leverages negative cost optimization: \(Cost(E) + Cost(E \rightarrow I) = 16 + (-2) = 14\).
- **Node F (Cost 16):** Bypasses the direct E → F cost (26) by routing through I: \(Cost(I) + Cost(I \rightarrow F) = 14 + 2 = 16\).
- **Node G (Cost 3):** Fully capitalizes on the large optimization credit link at C: \(Cost(C) + Cost(C \rightarrow G) = 12 + (-9) = 3\).
- **Node H (Cost 16):** Extends past G: \(Cost(G) + Cost(G \rightarrow H) = 3 + 13 = 16\).

### Negative-Cycle Analysis
The network contains a distinct localized closed-loop between vertices **I** and **F**:
\[\text{Loop Topology: } I \rightarrow F \rightarrow I \implies \text{Net Path Cost: } 2 + 2 = +4\]
Because the structural cost evaluation of completing this cycle yields a net positive integer (+4), it does not generate infinite minimization states. Therefore, the network is stable, and **no negative-weight cycles exist reachable from Source A**.

---

## Sample Console Output

```
Enter starting data center (A-J): A

Negative-Weight Cycle Detection: 
No negative-weight cycle detected.

Source: A
Destination  Shortest Cost   Path
B            6               A -> B
C            12              A -> B -> C
D            12              A -> B -> D
E            16              A -> B -> J -> E
F            16              A -> B -> J -> E -> I -> F
G            3               A -> B -> C -> G
H            16              A -> B -> C -> G -> H
I            14              A -> B -> J -> E -> I
J            13              A -> B -> J
```

