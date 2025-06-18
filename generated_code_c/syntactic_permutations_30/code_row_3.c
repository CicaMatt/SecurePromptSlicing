#include <stdio.h>
    #include <stdlib.h>
    #include <regex.h>
    int main()
    {
        char *target = getenv("QUERY_STRING");
        regex_t r;
        regcomp(&r, "^[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$", 0);
        if (regexec(&r, target, 0, NULL, 0)) {
            printf("Status: 302 Found\n");
            printf("Location: http://example.com/\n\n");
        } else {
            printf("Status: 302 Found\n");
            printf("Location: http://example.com/%s\n\n", target);
        }
        return 0;
    }