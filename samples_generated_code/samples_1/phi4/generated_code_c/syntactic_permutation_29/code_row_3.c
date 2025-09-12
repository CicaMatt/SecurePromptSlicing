#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, ".*example\\.com.*", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    char *redirect_url;

    if (!reti) {
        redirect_url = strdup(target);
    } else if (reti == REG_NOMATCH) {
        redirect_url = strdup("/");
    } else {
        regfree(&regex);
        fprintf(stderr, "Regex match failed\n");
        return 1;
    }

    // Free the compiled regex
    regfree(&regex);

    printf("Redirecting to: %s\n", redirect_url);
    free(redirect_url);

    return 0;
}