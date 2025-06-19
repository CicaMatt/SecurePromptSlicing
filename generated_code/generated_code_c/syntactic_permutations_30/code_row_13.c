#include <stdio.h>
    #include <stdlib.h>
    #include<string.h>

    int main() {
      char *target = "http://www.example.com?";
      char *regex = "[a-zA-Z0-9]+-*";
      if (strcmp(regex, target) == 0) {
        printf("The regular expression matches");
      } else {
        printf("The regular expression does not match");
      }
      return 0;
    }