---
layout: exercise
language: python
permalink: "Heap/Exercise1"
title: "CS 271: Tree Array Exercise"
excerpt: "CS 271: Tree Array Exercise"
canvasasmtid: "218982"
canvaspoints: "2"
canvashalftries: 5

info:
  comments: "true"
  prev: "./Video1"
  next: "./Video2"
  points: 2
  instructions: "Fill in the method <code>heap2tree</code> to convert the heap nodes in the list <code>heap</code> into a binary tree data structure."
  goals:
    - Manipulate basic graph data structures
    
processor:  
  correctfeedback: "Correct!!" 
  incorrectfeedback: "Try again"
  submitformlink: false
  feedbackprocess: | 
    var pos = feedbackString.trim();
  correctcheck: |
    pos.includes("62,43,41,27,40,41,2,20,77,38,29,79,62,17:10,64,67,22,43,61,43,26,20,18,30,35,52,38")
  incorrectchecks:
    - incorrectcheck: |
        pos.includes("20:26")
      feedback: "Try again.  It looks like your tree only has the root with no children.  Are you assigning all of the children relationships?"
files:
  - filename: "student.py"
    name: tree
    ismain: false
    isreadonly: false
    isvisible: true
    height: 600
    code: | 
          class TreeNode(object):
              def __init__(self, value):
                  self.value = value
                  self.left = None
                  self.right = None

              def inorder(self, arr):
                  if self.left:
                      self.left.inorder(arr)
                  arr.append(self.value)
                  if self.right:
                      self.right.inorder(arr)

          class BinaryTree(object):
              def __init__(self):
                  self.root = None

              def inorder(self):
                  arr = []
                  if self.root:
                      self.root.inorder(arr)
                  return arr

          def heap2tree(heap):
              """
              Parameters
              ----------
              heap: list of objects

              Returns
              -------
              tree: BinaryTree
                  A binary tree containing the data in the heap
              """
              tree = BinaryTree()
              if len(heap) > 0:
                  ## Step 1: Create a list of nodes for all of the
                  ## elements in the heap
                  nodes = []
                  for i in range(len(heap)):
                      obj = heap[i]
                      nodes.append(TreeNode(obj))

                  ## Step 2: Assign all of the children pointers properly
                  ## TODO: Fill this in.  Use the formula for the children indices
                  ## to find the children for each node, and link them together

                  ## Step 3: Make the root of the tree be the first element in nodes
                  tree.root = nodes[0]
              return tree



  - filename: "main.py"
    ismain: true
    name: main
    isreadonly: true
    isvisible: true
    code: |
        heap = [20, 27, 79, 43, 41, 38, 17, 62, 41, 40,  2, 77, 29, 62]
        tree = heap2tree(heap)
        arr = tree.inorder()
        s = ""
        for x in arr:
            s = s + "{},".format(x)

        heap = [26, 22, 35, 64, 61, 18, 38, 10, 67, 43, 43, 20, 30, 52]
        tree = heap2tree(heap)
        arr = tree.inorder()
        s = s[0:-1] + ":"
        for x in arr:
            s = s + "{},".format(x)
        
        print(s[0:-1])

openFilesOnLoad: ["main.py", "student.py"]
---
