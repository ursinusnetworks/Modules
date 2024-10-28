---
layout: exercise
language: "python"
permalink: "SpanningTrees/Exercise1"
title: "CS 271: Exercise on Constructing Spanning Trees"
excerpt: "CS 271: Exercise on Constructing Spanning Trees"
canvasasmtid: "207301"
canvaspoints: "2"
canvashalftries: 5

info:
  comments: "true"
  prev: "./Video1"
  next: "./Video2"
  points: 2
  instructions: "Fill in the code that uses union find to create a spanning tree from edges that are traversed in some specified order.  The key step is to skip edges that would create a cycle if added.  You can check to see if an edge will create a cycle by using a disjoint set data structure and seeing if the nodes it would connect already belong to the same component."
  goals:
    - Use union and find operations of a disjoint set data structure
    - Create spanning trees
    
processor:  
  correctfeedback: "Correct!!" 
  incorrectfeedback: "Try again"
  submitformlink: false
  feedbackprocess: | 
    var pos = feedbackString.trim();
  correctcheck: |
        pos.includes("(3, 1), (7, 3), (6, 2), (3, 2), (7, 4), (1, 0), (5, 1)")
  incorrectchecks:
    - incorrectcheck: |
        pos.includes("(3, 1), (7, 3), (6, 2), (3, 2), (7, 1), (7, 4), (1, 0), (6, 4), (7, 6), (2, 0), (4, 1), (5, 1), (5, 3), (6, 5), (6, 0), (5, 4), (2, 1), (3, 0), (7, 2), (5, 2), (4, 0), (7, 0), (4, 2), (6, 1), (4, 3), (6, 3), (5, 0), (7, 5)")
      feedback: "Try again.  It looks like you're adding every single edge still. Be sure to union nodes after adding edges"
files:
  - filename: "unionfind.py"
    name: unionfind
    ismain: false
    isreadonly: true
    isvisible: true
    height: 500
    code: | 
          # A fast version of union find using path compression and
          # rank-based merging
          class UFFast:
              def __init__(self, N):
                  self._parent = list(range(N))
                  self._rank = [1]*N
              
              def root(self, i):
                  """
                  Follow parent pointers until reaching a root
                  Parameters
                  ----------
                  i: int
                      The starting node 
                  
                  Returns
                  -------
                  The root node of i
                  """
                  p = i
                  while self._parent[p] != p:
                      p = self._parent[p]
                  j = i
                  # Path compression
                  while self._parent[j] != j:
                      j = self._parent[j]
                      self._parent[j] = p
                  return p

              def get_set_label(self, i):
                  """
                  Return a number that is the same for every element in
                  the set that i is in, and which is unique to that set
                  Parameters
                  ----------
                  i: int
                      Element we're looking for
                  
                  Returns
                  -------
                  Index of the bubble containing i
                  """
                  return self.root(i)
              
              def find(self, i, j):
                  """
                  Return true if i and j are in the same component, or
                  false otherwise
                  Parameters
                  ----------
                  i: int
                      Index of first element
                  j: int
                      Index of second element
                  """
                  return self.root(i) == self.root(j)
              
              def union(self, i, j):
                  """
                  Merge the two sets containing i and j, or do nothing if they're
                  in the same set
                  Parameters
                  ----------
                  i: int
                      Index of first element
                  j: int
                      Index of second element
                  """
                  root_i = self.root(i)
                  root_j = self.root(j)
                  if root_i != root_j:
                      if self._rank[root_i] < self._rank[root_j]:
                          self._parent[root_i] = root_j
                          self._rank[root_j] += self._rank[root_i]
                      else:
                          self._parent[root_j] = root_i
                          self._rank[root_i] += self._rank[root_j]


  - filename: "student.py"
    name: tree
    ismain: false
    isreadonly: false
    isvisible: true
    height: 600
    code: | 
          def get_spanning_tree(N, edges):
              """
              Parameters
              ----------
              N: int
                  Number of nodes
              edges: List of (i, j)
                  List of edges to add in some specified order
              
              Returns
              -------
              List of (i, j) edges that belong to the spanning tree
              """
              djset = UFFast(N)
              tree_edges = []
              for (i, j) in edges:
                  # Check in union find data structure djset to see
                  # if they are part of the same component, and hence
                  # would create a cycle.
                  makes_cycle = False
                  
                  if not makes_cycle:
                      ## TODO: Merge the two nodes in union find, and
                      ## add the edge to the spanning tree
                      
                      tree_edges.append((i, j))
              return tree_edges



  - filename: "main.py"
    ismain: true
    name: main
    isreadonly: true
    isvisible: true
    code: |
        edges = [(3, 1), (7, 3), (6, 2), (3, 2), (7, 1), (7, 4), (1, 0), (6, 4), (7, 6), (2, 0), (4, 1), (5, 1), (5, 3), (6, 5), (6, 0), (5, 4), (2, 1), (3, 0), (7, 2), (5, 2), (4, 0), (7, 0), (4, 2), (6, 1), (4, 3), (6, 3), (5, 0), (7, 5)]
        tree_edges = get_spanning_tree(8, edges)
        print(tree_edges)

openFilesOnLoad: ["main.py", "student.py"]
---
