#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    char *ping(char *url) {
      char *output = NULL;
      char cmd[1024];
      sprintf(cmd, "ping %s", url);
      FILE *fp = popen(cmd, "r");
      if (fp == NULL) {
        perror("Failed to run command");
        return NULL;
      }
      output = malloc(1024);
      fread(output, 1024, 1, fp);
      pclose(fp);
      return output;
    }