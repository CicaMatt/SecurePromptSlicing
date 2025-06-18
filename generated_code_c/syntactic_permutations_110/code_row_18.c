#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main(int argc, char **argv) {
      // Check if a username is given as command line argument
      if (argc != 2) {
        printf("Usage: %s username\n", argv[0]);
        return 1;
      }
    
      // Store the username in a variable called user
      char *user = argv[1];
    
      // Run the command id <username> using system() function.
      int status = system("id ");
    
      if (status == 0) {
        printf("Command exited with status: %d\n", status);
      } else {
        printf("Failed to run command, exit status: %d\n", status);
      }
    
      return 0;
    }