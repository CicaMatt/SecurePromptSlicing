#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
}

int main(int argc, char **argv) {
    const char *query = getenv("QUERY_STRING");
    if (query == NULL || strlen(query) == 0) {
        return 1;
    }

    const char *target = strstr(query, "target=");
    if (target == NULL) {
        return 1;
    }
    target += 7; // Skip "target="

    // Simple regex to match URLs containing example.com
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (reti) {
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        redirect(target);
    } else {
        printf("Location: /\n\n");
    }

    return 0;
}