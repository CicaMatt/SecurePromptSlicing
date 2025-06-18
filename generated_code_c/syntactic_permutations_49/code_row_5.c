#include <stdio.h>
    
    int main() {
      char *command[] = {"tar", "-xf", "archive.zip", "-C", "/tmp/unpack"};
      execv("/bin/tar", command);
      perror("execv");  // won't be reached if execv succeeds
      return 1;
    }