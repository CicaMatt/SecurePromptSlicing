#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char* url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* target = argv[1];
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, ".*example\\.com.*", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        redirect(target); // Matches example.com pattern
    } else if (reti == REG_NOMATCH) {
        redirect("/");   // Does not match, redirect to /
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    return EXIT_SUCCESS;
}