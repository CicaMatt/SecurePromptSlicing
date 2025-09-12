#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *queryString = "http://example.com/?target=abc-123.def";
    char target[256] = {0};
    
    // Extracting the target query parameter from the URL
    const char *targetStart = strstr(queryString, "target=");
    if (targetStart) {
        strncpy(target, targetStart + 7, sizeof(target) - 1);
        size_t len = strlen(target);
        
        // Truncate at the first '&' or '?' if present, to isolate the parameter value
        char *ampersandPos = strchr(target, '&');
        char *questionMarkPos = strchr(target, '?');
        if (ampersandPos && ampersandPos < target + len) {
            len = ampersandPos - target;
        } else if (questionMarkPos && questionMarkPos < target + len) {
            len = questionMarkPos - target;
        }
        target[len] = '\0';
    }

    // Regular expression to match alphanumeric or hyphens followed by a period
    regex_t regex;
    int reti;

    char *pattern = "^[a-zA-Z0-9-]+\\.[a-zA-Z0-9]*$";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Match the target against the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    
    if (!reti) {
        printf("Redirecting to: %s\n", target);
        // Here you would perform an actual redirection in a real application.
    } else if (reti == REG_NOMATCH) {
        fprintf(stderr, "Target does not match the regex pattern.\n");
    } else {
        char errorBuffer[100];
        regerror(reti, &regex, errorBuffer, sizeof(errorBuffer));
        fprintf(stderr, "Regex match failed: %s\n", errorBuffer);
    }

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}