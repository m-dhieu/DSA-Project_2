# IoT Gateway Connectivity Analyser

A smart agriculture company operates several IoT gateways that collect data from sensors deployed across different farm zones. Gateways communicate directly with nearby gateways to exchange sensor data.

Each gateway is represented as a node, while a direct communication link is represented as an edge. The number on each edge represents the average data-transfer time in milliseconds between the two gateways.

This project is an undirected graph-based connectivity analyser to analyse data-transfer times between smart agriculture IoT gateways using Breadth-First Search (BFS).

## Compilation and Execution

Compile using:

```bash
gcc gateway_analyser.c -o gateway_analyser
```

Then run:

```bash
./gateway_analyser
```

## Graph Representation
The network is mapped using a 7 × 7 Adjacency Matrix where index positions `0` through `6` correspond to gateways `A` through `G`. Disconnected paths hold a default weight value of `0`.

## Sample Output Trace

### Case 1: Standard Valid Run (Gateway D)
```
Enter starting gateway: D
A B C E F 
E : 22 ms
```

### Case 2: Validation Check (Invalid Node Input)
```
Enter starting gateway: Z
Error: Gateway 'Z' does not exist in the network.
```

