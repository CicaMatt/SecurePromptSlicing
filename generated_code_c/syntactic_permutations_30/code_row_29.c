#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <regex.h>
    
    int main(int argc, char** argv) {
        char target[1024];
        sprintf(target, "%s", getenv("QUERY_STRING"));
        regex_t r;
        regcomp(&r, "^\\w+-*\\.", REG_EXTENDED);
        if (regexec(&r, target, 0, NULL, 0) == REG_NOMATCH) {
            printf("Location: /\n\n");
        } else {
            printf("Location: %s\n\n", target);
        }
    
        return 0;
    }