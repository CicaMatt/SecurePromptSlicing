#include <stdio.h>
    #include <string.h> 
    #include <stdlib.h>

    char *ping(char *url) {
      char *cmd = malloc(1024);
      sprintf(cmd, "ping %s", url);
      return system(cmd);
    }