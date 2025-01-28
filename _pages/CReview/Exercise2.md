---
layout: exercise
language: "cpp"
permalink: /CReview/Exercise2
title: "malloc exercise"
canvasasmtid: "229134"
canvaspoints: 1.5

info:
  prev: "./Video3"
  points: 1.5
  instructions: "With the help of <code>sscanf</code> complete the method <code>extractVersion</code> to extract the major and minor version number from a string.  For example, if the string is \"3.14\", the major version is 3 and the minor version is 14."
  goals:
    - Use sprintf to parse a string
    - Pass values by reference
    - Dereference pointers
    
processor:  
  correctfeedback: "Correct!!" 
  incorrectfeedback: "Try again"
  submitformlink: false
  feedbackprocess: | 
    var pos = runtime.text.trim();
  correctcheck: |
    pos.includes("3,14:47,5:1,74:") 
 
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
        @param verStr: The version string
        @param major: A pointer to the int that should hold the major version
                      when this method is done
        @param minor: A pointer to the int that should hold the minor version
                      when this method is done
        */
        void extractVersion(const char* verStr, int* major, int* minor) {
            // TODO: Fill this in
        }


  - filename: "driver.cpp"
    name: main
    ismain: true
    isreadonly: true
    isvisible: true
    code: | 
      int main() {
          int major, minor;
          extractVersion("3.14", &major, &minor);
          printf("%i,%i:", major, minor);
          extractVersion("47.5", &major, &minor);
          printf("%i,%i:", major, minor);
          extractVersion("1.74", &major, &minor);
          printf("%i,%i:", major, minor);
          printf("\n");
      }
        
openFilesOnLoad: ["driver.cpp", "student.cpp"]
---