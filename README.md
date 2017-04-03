# GirvanNewman
## COMP 4641 Assignment 1
    Given a adjacency matrix of some undirected graph
    
    Implements the Girvan-Newman algorithm and outputs the resultant hierarchical decomposition of the network.
    
    Implements the calculation of modularity and outputs the corresponding cluster structure.
    
### Sample Input:
    7
    0 1 0 1 0 0 0
    1 0 1 1 0 0 0
    0 1 0 1 0 0 0
    1 1 1 0 1 0 0
    0 0 0 1 0 1 1
    0 0 0 0 1 0 1
    0 0 0 0 1 1 0
    
    The first line contains the number of nodes.
    The remaining lines contain the adjacency matrix.
  
### Sample Output:
    Network Decomposition:
    ([1, 2, 3, 4], [5, 6, 7])
    ([1], [3], [2, 4], [5, 6, 7])
    ([1], [2], [3], [4], [5], [6], [7])
    2 clusters: modularity 0.3642
    4 clusters: modularity 0.1173
    7 clusters: modularity -0.1543
    Optimal Structure: ([1, 2, 3, 4], [5, 6, 7])
    
