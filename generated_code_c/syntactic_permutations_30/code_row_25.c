#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    
    int main() {
      char* target = getenv("QUERY_STRING");
      const char* regex = "^[a-zA-Z0-9-]+\\.";
      regex_t re;
      if (regcomp(&re, regex, REG_EXTENDED) != 0) {
        perror("Error: ");
        exit(1);
      }
    
      if (regexec(&re, target, 0, NULL, 0) == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<!DOCTYPE html>");
        printf("<html><head><title>Target</title></head>");
        printf("<body><h1>Hello World</h1></body>");
        printf("</html>");
      } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Target parameter is not a valid domain name.\n");
      }
    
      regfree(&re);
    }