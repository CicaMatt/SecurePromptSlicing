#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define REDIRECT_URL "https://www.example.com"

void handle_redirect(const char *target_query) {
    regex_t regex;
    int reti;
    char redirect_url[256] = REDIRECT_URL;

    // Compile the regular expression
    reti = regcomp(&regex, "^([a-zA-Z0-9]+(-)*\\.)+", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, target_query, 0, NULL, 0);

    if (!reti) {
        printf("Redirecting to: %s\n", target_query);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to: %s\n", redirect_url);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    printf("Final redirect URL: ");
    if (!reti) {
        printf("%s\n", target_query);
    } else {
        printf("%s\n", redirect_url);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_query>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    handle_redirect(argv[1]);

    return EXIT_SUCCESS;
}