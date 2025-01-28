---
layout: exercise
language: "cpp"
permalink: /CReview/Exercise1
title: "malloc exercise"
canvasasmtid: "229132"
canvaspoints: 1.5

info:
  prev: "./Video1"
  next: "./Video2"
  points: 1.5
  instructions: "Complete the method <code>getArray</code> to dynamically allocate an array of shorts with \"num\" elements, where every single element is the number 475."
  goals:
    - Use malloc in C
    - Use loops in C
    
processor:  
  correctfeedback: "Correct!!" 
  incorrectfeedback: "Try again"
  submitformlink: false
  feedbackprocess: | 
    var pos = runtime.text.trim();
  correctcheck: |
    pos.includes("475.475.475.475.475.475.475.475.475.475:475.475.475.475.475:") 
 
files:
  - filename: "student.cpp"
    name: student
    ismain: false
    isreadonly: false
    isvisible: true
    code: | 
        #include <stdio.h>
        #include <stdlib.h>

        /**
        @param num: Number of elements in the array
        */
        short* getArray(int num) {
            // TODO: Fill this in
        }


  - filename: "driver.cpp"
    name: main
    ismain: true
    isreadonly: true
    isvisible: true
    code: | 
      int main() {
          int N = 10;
          short* x = getArray(N);
          for (int i = 0; i < N; i++) {
              printf("%i", x[i]);
              if (i < N-1) {
                  printf(".");
              }
          }
          free(x);
          N = 5;
          x = getArray(N);
          printf(":");
          for (int i = 0; i < N; i++) {
              printf("%i", x[i]);
              if (i < N-1) {
                  printf(".");
              }
          }
          free(x);
          printf(":\n");
      }
        
openFilesOnLoad: ["driver.cpp", "student.cpp"]
---