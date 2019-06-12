# Graph-Theory-Project-Template
Project template of course - Graph Theory (EE6622E) in National Cheng Kung University.

This program can only deal with undirected graph.

## How to run

```
1. Put your topo-file "topo.txt" to /Graph-Theory-Project-Template/
2. execute "make" command
3. execute "./main.out" command
```



## Output

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
All of the node in graph is even degree then there exist an Euler Circuit.

If odd degree node exist that means it must walk on some edges not only one time.

The repeat path can be thought as adding another edge and walking on it.

So, our goal is to "make all node with even degree"

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
```
1. Count the number of node and edge
2. Build the adjacency matrix
3. Determine degree of each Node
4. Add edges along path between 2 odd degree node 
5. Update adjacency matrix
6. Find Euler Path
```
## Algorithm I use

### Dijkstra

There are 3 variable :

    distant[] : distant from source to the node.

    parent[] : last node come from the path.
    
    visit[] : false => node is not visited.
              true  => node is visited.
                        
Concept

```
Initail : 
          source.distant = 0. ohter_node.distant = infinity.
          source.parent = source. other_node.parent = NIL.
          
1. If there are unvisited node.

   u = unvisited node with min(distant), the node we want to visit now.
   
   u.visit = true;
   
2. for every node v (adjacent node of u && unvisited)

    - Update the distant if (distant[v] < edge(u,v) + distant[u])
    
    - u.parent = v;
    
Repeat step1,2 until all node has visited.
```

### Find_Path

    Given a source and destination
    
    Use the parent[] we just build from Dijkstra algorithm.
    
    Use recusive to trace the parent of destination until parent = source.

### EulerCircuit
Just like DFS algorithm.
```
1. When we find a edge can walk, just walk it until no edge can walk.

2. Trace back the edge and put the edge into the trails.

Repeat step1 & step2 until all node has been visited.
```
