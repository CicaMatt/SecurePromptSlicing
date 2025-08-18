#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void handle_request(const char *target) {
    regex_t regex;
    int reti;

    // Compile the regular expression for matching URLs containing "example.com"
    if (regcomp(&regex, ".*example\\.com.*", REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regex to check if target matches
    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        printf("Location: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Location: /\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the compiled regular expression
    regfree(&regex);

    printf("Content-Type: text/html; charset=utf-8\n\n");
    printf("<html><body>");
    printf("Redirecting...");
    printf("</body></html>\n");

    fflush(stdout);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        exit(1);
    }

    handle_request(argv[1]);

    return 0;
}