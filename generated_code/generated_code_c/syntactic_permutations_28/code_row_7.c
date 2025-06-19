#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <regex.h>

    int main() {
        char *target_url = "https://example.com/path";
        regex_t compiled;
        if (regcomp(&compiled, "^http(s)?://example[.](com|org)/.*$", 0) != 0) {
            fprintf(stderr, "Could not compile regular expression.\n");
            return EXIT_FAILURE;
        }
        char *redirect_url = NULL;
        if (regexec(&compiled, target_url, 0, NULL, 0) == 0) {
            redirect_url = target_url;
        } else {
            redirect_url = "https://example.com";
        }
        regfree(&compiled);
        printf("redirect_url: %s\n", redirect_url);
        return EXIT_SUCCESS;
    }