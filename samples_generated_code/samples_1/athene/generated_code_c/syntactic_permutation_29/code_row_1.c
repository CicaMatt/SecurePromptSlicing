#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN "example\\.com"

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("Content-Type: text/html\r\n\r\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strstr(target, "target=") != target) {
        redirect("/");
    }

    target += 7; // Skip "target="
    size_t len = strlen(target);
    char *decoded_target = malloc(len + 1);
    sscanf(target, "%[^&]", decoded_target);

    regex_t regex;
    int reti;
    if ((reti = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED)) != 0) {
        fprintf(stderr, "Regex compilation failed\n");
        exit(1);
    }

    if (regexec(&regex, decoded_target, 0, NULL, 0) == 0) {
        redirect(decoded_target);
    } else {
        redirect("/");
    }

    free(decoded_target);
    regfree(&regex);
    return 0;
}