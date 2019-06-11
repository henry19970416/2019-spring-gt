# Graph-Theory-Project-Template
Project template of course - Graph Theory (EE6622E) in National Cheng Kung University.

This program can only deal with undirected graph.

## How to run

```
1. Put your topo-file "topo.txt" to /Graph-Theory-Project-Template/
2. execute "make" command
3. execute "./main.out" command
```



## Solution

Solution will be show in 2 ways

* File
```
A output file "solution.txt" with the path
```

* Cout
```
1. show adjacent matrix initial
2. show adjacent matrix again after adding some edge
3. show the Path
```
## How does program run

* Idea
```
- If all node has even degree. 
  Solution exist.
  Find the solution directely.

- If there are some node with odd degree. 
  Add some extra edge along the path between 2 odd degree node.
  Make all of the nodes has even degree.
  Find the solution.
  
```

* Step of the program

After read in the topo.txt

1. Count the number of node and edge
2. Build the adjacency matrix
3. Determine degree of each Node
4. Add edges along path between 2 odd degree node 
5. Update adjacency matrix
6. Find Euler Path
