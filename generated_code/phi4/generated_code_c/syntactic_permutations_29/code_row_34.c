#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

void handle_request(const char *target) {
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, ".*", REG_EXTENDED);
    if (reti) {
        printf("Could not compile regex\n");
        exit(1);
    }

    // Execute regex match
    reti = regexec(&regex, target, 0, NULL, 0);
    
    if (!reti) { 
        printf("Redirecting to: %s\n", target); // Simulate redirection by printing
    } else {
        if (reti == REG_NOMATCH) {
            printf("Target does not match regex. Redirecting to: /\n");
        }
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    handle_request(argv[1]);

    return 0;
}