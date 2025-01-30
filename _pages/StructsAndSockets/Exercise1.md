---
layout: exercise
language: "cpp"
permalink: /StructsAndSockets/Exercise1
title: "Linked List C Exercise"
canvasasmtid: "229307"
canvaspoints: 2

info:
  prev: "./Video1"
  next: "./Video2"
  points: 2
  instructions: "<p>Define a method <code>LinkedList_removeFirst</code> which removes the first node from the array and returns the element that it contained.  If the list is empty, it should return NULL.</p>"
  goals:
    - Work with structs in C
    - Properly dereference pointers in C
    - Implement linked list methods
    
processor:  
  correctfeedback: "Correct!!" 
  incorrectfeedback: "Try again"
  submitformlink: false
  feedbackprocess: | 
    var pos = runtime.text.trim();
  correctcheck: |
    pos.includes("Layla,YeetTheo ==> Celia ==> Chris ==>") 
 
files:
  - filename: "student.cpp"
    name: student
    ismain: false
    isreadonly: false
    isvisible: true
    code: | 
          #include <stdio.h>
          #include <stdlib.h>

          struct Node {
              struct Node* next;
              void* data;
          };

          struct LinkedList {
              struct Node* head;
          };

          // TODO: Add method here (so you don't have to scroll down)

          struct LinkedList* LinkedList_init() {
              struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
              list->head = NULL;
              return list;
          }

          void LinkedList_free(struct LinkedList* list) {
              // Step 1: Clean up nodes
              struct Node* node = list->head;
              while (node != NULL) {
                  struct Node* nextNode = node->next;
                  free(node);
                  node = nextNode;
              }
              // Step 2: Free list
              free(list);
          }

          void LinkedList_addFirst(struct LinkedList* list, void* data) {
              struct Node* newHead = (struct Node*)malloc(sizeof(struct Node));
              struct Node* head = list->head;
              newHead->next = list->head;
              newHead->data = data;
              list->head = newHead;
          }

          void LinkedList_print(struct LinkedList* list) {
              struct Node* node = list->head;
              while (node != NULL) {
                  printf("%s ==> ", (char*)node->data);
                  node = node->next;
              }
              printf("\n");
          }


  - filename: "driver.cpp"
    name: main
    ismain: true
    isreadonly: true
    isvisible: true
    code: | 
          int main() {
              struct LinkedList* list = LinkedList_init();
              LinkedList_addFirst(list, (void*)"Chris");
              LinkedList_addFirst(list, (void*)"Celia");
              LinkedList_addFirst(list, (void*)"Theo");
              LinkedList_addFirst(list, (void*)"Layla");
              char* s1 = (char*)LinkedList_removeFirst(list);
              LinkedList_addFirst(list, (void*)"Yeet");
              char* s2 = (char*)LinkedList_removeFirst(list);
              printf("%s,%s", s1, s2);
              LinkedList_print(list);
              printf("\n");
              LinkedList_free(list);
          }
        
openFilesOnLoad: ["driver.cpp", "student.cpp"]
---