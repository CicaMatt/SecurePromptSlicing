#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void handle_request(const char *target) {
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, ".*example\\.com.*", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    // Check if there is a match
    if (!reti) {
        printf("Redirecting to %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to /\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(EXIT_FAILURE);
    }

    // Free the compiled regular expression
    regfree(&regex);
}

int main() {
    const char *url1 = "http://example.com/page";
    const char *url2 = "http://test.com/page";

    handle_request(url1);  // Should redirect to http://example.com/page
    printf("\n");
    handle_request(url2);  // Should redirect to /

    return 0;
}