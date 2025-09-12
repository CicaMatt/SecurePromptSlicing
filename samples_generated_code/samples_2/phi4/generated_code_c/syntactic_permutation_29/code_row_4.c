#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pattern = ".*example\\.com.*";
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute regular expression
    reti = regexec(&regex, argv[1], 0, NULL, 0);

    char *redirect_url;
    if (!reti) {
        printf("Redirecting to: %s\n", argv[1]);
        redirect_url = strdup(argv[1]);
    } else {
        if (reti != REG_NOMATCH) {
            regfree(&regex);
            fprintf(stderr, "Regex match failed with unexpected error code.\n");
            return EXIT_FAILURE;
        }
        printf("Redirecting to: /\n");
        redirect_url = strdup("/");
    }

    // Simulate a web server redirection
    printf("HTTP/1.1 302 Found\nLocation: %s\n\n", redirect_url);

    regfree(&regex);
    free(redirect_url);

    return EXIT_SUCCESS;
}