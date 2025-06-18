#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    int main(int argc, char *argv[]) {
      if (argc != 2) {
        printf("Usage: %s username\n", argv[0]);
        return 1;
      }
      char command[1024];
      sprintf(command, "cat /etc/passwd | grep %s", argv[1]);
      system(command);
      return 0;
    }