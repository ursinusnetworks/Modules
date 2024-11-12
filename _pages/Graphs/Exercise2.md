---
layout: exercise
language: python
permalink: "Graphs/Exercise2"
title: "CS 271: Graph 2 hops"
excerpt: "CS 271: Graph 2 Hops"
canvasasmtid: "207264"
canvaspoints: "2"
canvashalftries: 5

info:
  comments: "true"
  prev: "./Video2"
  next: "./Video3"
  points: 2
  instructions: "Fill in the method <code>get_reachable_2_hops</code> to compute the set of nodes that are reachable from a particular node within 1 or 2 hops.  The picture below shows an example of all of the node that are within 1 and two hops of a particular node:<p></p><img src = \"../images/Graphs/TwoHops.svg\" width=\"30%\">"
  goals:
    - Manipulate neighbor data structure and sets in graphs
    
processor:  
  correctfeedback: "Correct!!" 
  incorrectfeedback: "Try again"
  submitformlink: false
  feedbackprocess: | 
    var pos = feedbackString.trim();
  correctcheck: |
    pos.includes("[0, 1, 2, 3, 4]_[1, 3, 4, 5]")
  incorrectchecks:
    - incorrectcheck: |
        pos.includes("[]_[]")
      feedback: "Try again.  It looks like you're still returning empty sets"
    - incorrectcheck: |
        pos.includes("[0, 1, 2, 3, 4]_[1, 4, 5]")
      feedback: "Try again.  It looks like you're only returning exactly two hops!  Be sure also to include the 1 hop vertices, which you can get directly from the neighbors"
files:
  - filename: "student.py"
    name: tree
    ismain: false
    isreadonly: false
    isvisible: true
    height: 600
    code: | 
          class AdjacencyGraph:
              def __init__(self):
                  self.neighbs = {}
              
              def add_vertex(self, v):
                  self.neighbs[v] = set([])
              
              def add_edge(self, u, v):
                  self.neighbs[u].add(v)
                  self.neighbs[v].add(u)
              
              def get_neighbors(self, v):
                  return self.neighbs[v]
              
              def is_edge(self, u, v):
                  return u in self.neighbs[v] and v in self.neighbs[u]
              
              def get_reachable_2_hops(self, u):
                  """
                  Fill in the set of all vertices that are reachable
                  from u after one or two hops; that is, v is in this
                  reachable set if there exists some path u->v or u->k->v
                  """
                  reachable = set([])
                  ## TODO: Fill this in
                  return reachable


  - filename: "main.py"
    ismain: true
    name: main
    isreadonly: true
    isvisible: true
    code: |
        graph = AdjacencyGraph()
        for v in range(6):
            graph.add_vertex(v)
        graph.add_edge(0, 1)
        graph.add_edge(1, 2)
        graph.add_edge(1, 4)
        graph.add_edge(4, 3)
        graph.add_edge(1, 3)
        graph.add_edge(0, 0)
        graph.add_edge(3, 5)
        s = "{}".format(sorted(graph.get_reachable_2_hops(0)))
        s += "_{}".format(sorted(graph.get_reachable_2_hops(5)))
        print(s)

openFilesOnLoad: ["main.py", "student.py"]
---
