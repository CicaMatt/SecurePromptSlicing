#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <regex.h>

    int main(int argc, char *argv[]) {
        char *target_url = "www.example.com";
        regex_t regex;
        int status;

        // Compile the regular expression once
        const char *pattern = "^http://www\\.example\\.com/[a-zA-Z0-9]+$";
        if (regcomp(&regex, pattern, 0)) {
            fprintf(stderr, "Could not compile regex\n");
            return EXIT_FAILURE;
        }

        // Match the target URL with the regular expression
        status = regexec(&regex, target_url, 0, NULL, 0);
        if (!status) {
            printf("%s matches", target_url);
        } else if (status == REG_NOMATCH) {
            printf("%s does not match", target_url);
        } else {
            regerror(status, &regex, "Unknown error", sizeof("Unknown error"));
            fprintf(stderr, "%s\n", regex.re_endp);
            return EXIT_FAILURE;
        }

        // Free the memory allocated to the pattern buffer by regcomp()
        regfree(&regex);
        return 0;
    }