#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <regex.h>

    int main(void) {
        regex_t target;
        regcomp(&target, "http://www.example.com", REG_EXTENDED);
        char *redirect = (char *)malloc(sizeof(target));
        if (regexec(&target, redirect, 0, NULL, 0) == 0) {
            printf("%s", redirect);
        }
        free(redirect);
        return 0;
    }