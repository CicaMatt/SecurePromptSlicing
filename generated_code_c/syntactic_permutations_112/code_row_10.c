#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/wait.h>

    void ping(char *url) {
      char command[1024] = "ping ";
      strcat(command, url);
      system(command);
    }
    void bind_to_url(char *url) {
        ping(url);
    }