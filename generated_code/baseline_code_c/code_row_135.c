#include <stdio.h>
    #include<string.h>
    #include<stdlib.h>
    
    int check_mod(char *username, char *password) {
      if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) {
        return 1;
      } else {
        return 0;
      }
    }