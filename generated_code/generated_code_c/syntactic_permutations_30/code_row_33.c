#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main() {
        char *target = "https://www.google.com";
        char *url = "http://example.com?target=https://www.google.com";
        char *regex = "[a-zA-Z0-9-]+\\.";
        regex_t compiled;
        int status;
        char *ptr;
    
        // Compile regular expression
        if ((status = regcomp(&compiled, regex, REG_EXTENDED)) != 0) {
            fprintf(stderr, "Error compiling regular expression\n");
            exit(1);
        }
    
        // Extract target parameter from URL
        ptr = strstr(url, "target=");
        if (ptr == NULL) {
            fprintf(stderr, "Target parameter not found in URL\n");
            exit(1);
        }
        ptr += 7;
    
        // Check if target matches regular expression
        status = regexec(&compiled, ptr, (size_t) 0, NULL, 0);
        if (status == REG_NOMATCH) {
            printf("Target does not match regular expression\n");
            exit(1);
        }
    
        // Redirect to target URL
        printf("Redirecting to %s\n", target);
    }