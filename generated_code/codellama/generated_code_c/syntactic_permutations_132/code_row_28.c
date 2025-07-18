#include <stdio.h>
    #include <string.h>
    
    void hello(char *username) {
      char *file = "hello.html";
      printf("Content-type: text/html\n");
      printf("Content-length: %d\n", strlen(file));
      printf("\n\n%s\n", file);
    }