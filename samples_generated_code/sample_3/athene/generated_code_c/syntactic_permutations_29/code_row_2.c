#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX "example\\.com"

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("Content-Type: text/html\r\n\r\n");
    exit(0);
}

int main() {
    char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) == 0) {
        redirect("/");
    }

    // Extract target parameter
    const char *prefix = "target=";
    size_t prefix_len = strlen(prefix);
    if (strncmp(target, prefix, prefix_len) != 0) {
        redirect("/");
    }
    target += prefix_len;

    // Compile regular expression
    regex_t regex;
    int reti = regcomp(&regex, REGEX, REG_EXTENDED | REG_NOSUB);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Check if target matches the regex
    if (regexec(&regex, target, 0, NULL, 0) == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    regfree(&regex);
    return 0;
}