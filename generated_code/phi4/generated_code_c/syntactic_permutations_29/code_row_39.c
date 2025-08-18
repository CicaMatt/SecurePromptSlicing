#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048

void redirect_to(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, "^https?://[^\\s/$.?#].[^\\s]*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        redirect_to(target);
    } else {
        redirect_to("/");
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    return EXIT_SUCCESS;
}