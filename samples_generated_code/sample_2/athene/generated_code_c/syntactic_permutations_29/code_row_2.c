#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define MAX_URL_LENGTH 1024

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main() {
    const char *query = getenv("QUERY_STRING");
    if (query == NULL || strstr(query, "target=") != query) {
        redirect("/");
    }

    char target[MAX_URL_LENGTH] = "";
    sscanf(query, "target=%1023s", target);

    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = "example\\.com";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        redirect("/");
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (reti == REG_NOMATCH) {
        redirect("/");
    } else {
        redirect(target);
    }

    regfree(&regex);
    return 0;
}