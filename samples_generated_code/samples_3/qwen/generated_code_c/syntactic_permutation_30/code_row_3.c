#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=abc-123.";
    const char *prefix = "target=";
    const char *url_prefix = "http://example.com/";
    char target[256];
    regex_t regex;
    int reti;

    // Extract the value of the target query parameter
    if (strncmp(query, prefix, strlen(prefix)) == 0) {
        strncpy(target, query + strlen(prefix), sizeof(target));
        target[sizeof(target) - 1] = '\0'; // Ensure null-termination
    } else {
        printf("Invalid query format.\n");
        return 1;
    }

    // Compile the regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        char redirect_url[512];
        snprintf(redirect_url, sizeof(redirect_url), "%s%s", url_prefix, target);
        printf("Redirecting to: %s\n", redirect_url);
        // In a real application, you would perform the redirection here.
    } else if (reti == REG_NOMATCH) {
        puts("No match");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you want to use it later
    regfree(&regex);

    return 0;
}