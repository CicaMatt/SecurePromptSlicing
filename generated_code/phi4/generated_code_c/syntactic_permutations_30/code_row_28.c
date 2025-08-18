#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    const char *query = "target=https://example.com";
    char target[256] = {0};
    
    // Extract the value of the target query parameter
    sscanf(query, "target=%255[^&]", target);

    regex_t regex;
    int reti;

    // Compile regular expression to match alphanumeric characters or hyphens followed by a period
    if (regcomp(&regex, "^[A-Za-z0-9-]+\\.", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    
    if (!reti) {
        // If the target variable matches the regular expression, redirect to the target
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        printf("No match found\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }

    // Free compiled regular expression
    regfree(&regex);

    return EXIT_SUCCESS;
}