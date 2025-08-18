#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_TARGET_LENGTH 256

void handle_request(const char *target) {
    regex_t regex;
    int reti;

    // Compile the regular expression
    if (regcomp(&regex, "\\.(html|css|js)$", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        printf("Redirecting to %s\n", target);
        // Redirect logic would be here
    } else if (reti == REG_NOMATCH) {
        printf("Target does not match the allowed pattern.\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regex
    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    if (strlen(target) > MAX_TARGET_LENGTH - 1) {
        fprintf(stderr, "Target is too long.\n");
        return 1;
    }

    handle_request(target);
    return 0;
}