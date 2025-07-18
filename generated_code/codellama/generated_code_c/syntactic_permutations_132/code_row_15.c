#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void say_hello(char *username) {
      printf("Hello, %s!", username);
    }

    int main() {
      char *username = "John Doe";
      say_hello(username);
      return 0;
    }