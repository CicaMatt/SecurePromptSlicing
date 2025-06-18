#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void ping(char *url) {
      char pong[1024];
      snprintf(pong, sizeof(pong), "ping %s", url);
      system(pong);
      if (WEXITSTATUS(exit_status)) {
        return 0;
      }
    }
    
    int main() {
      char *url = "https://www.example.com";
      ping(url);
      return 0;
    }