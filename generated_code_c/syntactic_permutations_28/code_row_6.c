#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(int argc, char **argv) {
        if (argc != 3)
            return 1;

        const char *url = "https://example.com";
        const char *regex = argv[2];
        char *redirect_url = calloc(100, sizeof(char));

        regex_t reg;
        if (regcomp(&reg, regex, REG_EXTENDED) != 0) {
            fprintf(stderr, "Error: invalid regular expression\n");
            return 2;
        }

        if (regexec(&reg, url, 0, NULL, 0) == 0) {
            strcpy(redirect_url, argv[1]);
            printf("%s", redirect_url);
            free(redirect_url);
            regfree(&reg);
        } else {
            fprintf(stderr, "Error: no match\n");
            return 3;
        }

        return 0;
    }