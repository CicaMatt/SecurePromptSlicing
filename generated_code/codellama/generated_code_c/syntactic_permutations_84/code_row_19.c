#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main() {
      const char* port = "5000";
      char buffer[1024];
    
      printf("Listening on port %s\n", port);
      
      while(fgets(buffer, 1024, stdin)) {
        if (strstr(buffer, "?param=") != NULL) {
          char* param = strtok(buffer, "&");
          
          if (strcmp(param, "Create") == 0) {
            printf("Error: Create is not a valid type\n");
          } else {
            // Parse as YAML and process request
          }
        } else {
          printf("Missing parameter 'param'\n");
        }
      }
    
      return 0;
    }