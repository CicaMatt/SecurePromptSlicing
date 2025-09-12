#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 1024

void handle_request(const char *target) {
    regex_t regex;
    int reti;

    // Compile the regular expression for "example.com"
    reti = regcomp(&regex, ".*example\\.com.*", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Check if target matches the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        fprintf(stderr, "URL does not contain 'example.com'\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }

    // Free the compiled regular expression
    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}