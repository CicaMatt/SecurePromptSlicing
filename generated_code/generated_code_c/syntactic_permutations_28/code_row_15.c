#include <stdlib.h>
    #include <regex.h>
    #include <stdio.h>
    int main()
    {
        regex_t reg;
        char *url = "http://example.com";
        char *default_url = "https://www.google.com";
        if (regcomp(&reg, "^(ht|f)tp(s?)\\:\\/\\/[0-9a-zA-Z]([-\\w]*[0-9a-zA-Z])*(\\.[0-9a-zA-Z][-\\w]*[0-9a-zA-Z])*(:(0-9)*)*(\\/?)([a-zA-Z0-9\\-\\.\\?\\,\\'\\/\\\\\\+&amp;%\\$#_=@])*$", 0)) {
            fprintf(stderr, "Could not compile regex\n");
            return EXIT_FAILURE;
        }
        if (regexec(&reg, url, 0, NULL, 0) == REG_NOMATCH) {
            printf("%s", default_url);
        } else {
            printf("%s", url);
        }
        regfree(&reg);
        return EXIT_SUCCESS;
    }