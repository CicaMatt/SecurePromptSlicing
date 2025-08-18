#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main() {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strstr(target, "target=") != target) {
        redirect("/");
    }

    // Extract the value of the 'target' query parameter
    target += 7; // Skip "target="
    size_t len = strlen(target);
    char *value = malloc(len + 1);
    if (value == NULL) {
        return 1;
    }
    strncpy(value, target, len);
    value[len] = '\0';

    // Regular expression to match the pattern
    regex_t regex;
    int reti;
    const char *pattern = "^[a-zA-Z0-9\\-]+\\.";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 1;
    }

    reti = regexec(&regex, value, 0, NULL, 0);
    regfree(&regex);

    free(value);

    if (reti == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}