#include <stdio.h>
#include <string.h>
#include <regex.h>

int main() {
    char *query = "target=abc123-def456.";
    char *target = NULL;
    char *start, *end;

    // Extract target from query string
    if (strstr(query, "target=")) {
        start = strchr(query, '=') + 1;
        end = strchr(start, '&');
        if (!end) {
            end = start + strlen(start);
        }
        int len = end - start;
        target = malloc(len + 1);
        strncpy(target, start, len);
        target[len] = '\0';
    }

    // Regular expression to match the pattern
    regex_t regex;
    const char *pattern = "^[a-zA-Z0-9\\-]+\\.$";
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Could not compile regex\n");
        return 1;
    }

    // Check if target matches the pattern
    if (target && regexec(&regex, target, 0, NULL, 0) == 0) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to root of site\n");
    }

    // Clean up
    if (target) free(target);
    regfree(&regex);

    return 0;
}