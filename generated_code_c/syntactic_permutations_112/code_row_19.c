#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void ping(char *url) {
      char cmd[1024];
      sprintf(cmd, "ping %s", url);
      system(cmd);
    }

    int main(void) {
      char *url = "example.com";
      ping(url);
      return 0;
    }