#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 1024

void redirect(char *target) {
    char command[1035];
    snprintf(command, sizeof(command), "http://example.com/%s", target);
    printf("Location: %s\n\n", command);
}

int main() {
    const char *query_string = getenv("QUERY_STRING");
    if (!query_string) {
        redirect("");
        return 0;
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile the regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    char *target = strchr(query_string, '=');
    if (target) {
        target++; // Move past '='
        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            redirect(target);
        } else if (reti == REG_NOMATCH) {
            redirect("");
        } else {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    } else {
        redirect("");
    }

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}