#include <stdio.h>
    #include <string.h>
    
    char* escape(char* s) {
      // Implementation not provided for this task
    }
    
    void hello(char* username) {
      char* msg = "Hello, %s!";
      printf(msg, escape(username));
    }