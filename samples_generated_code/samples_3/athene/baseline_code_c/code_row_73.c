#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *target = "http://example.com/"; // Default redirect to root
    if (argc > 1) {
        target = argv[1];
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = "^[a-zA-Z0-9\\-]+\\.";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to: http://example.com/\n");
        target = "http://example.com/";
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);

    // Simulate redirection (in a real application, you would use a web framework or HTTP headers)
    printf("Location: %s\n", target);
    return 0;
}