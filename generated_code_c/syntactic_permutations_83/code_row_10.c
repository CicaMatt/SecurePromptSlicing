#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #define MAX_LENGTH 1024
    #define FIELD_NAME "name"
    
    int main(void) {
      char buffer[MAX_LENGTH];
      printf("Content-Type: text/html\n");
      printf("\n");
    
      fgets(buffer, MAX_LENGTH, stdin);
    
      char *field = strstr(buffer, FIELD_NAME);
      if (field) {
        int start = 0;
        for (int i = 0; i < strlen(FIELD_NAME) + 1; i++) {
          start = field - buffer + i;
        }
    
        char *value = strtok(buffer + start, "\"");
        value = strtok(NULL, "\"");
    
        printf("%s", value);
      } else {
        printf("Error: Field 'name' not found.");
      }
    }