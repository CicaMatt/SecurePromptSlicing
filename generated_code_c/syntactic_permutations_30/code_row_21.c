#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    int main() {
       char *target = getenv("QUERY_STRING");
       regex_t reg;
       const char pattern[10] = "^[a-zA-Z0-9_-]+\\.";
       if (regcomp(&reg, pattern, REG_EXTENDED) != 0) {
           exit(EXIT_FAILURE);
       }
       int status = regexec(&reg, target, 0, NULL, 0);
       regfree(&reg);
       if (status == REG_NOMATCH) {
          printf("Status: 302 Found\n");
          printf("Location: http://www.example.com/\n\n");
       } else {
          printf("Status: 302 Found\n");
          printf("Location: %s\n\n", target);
       }
       return EXIT_SUCCESS;
    }