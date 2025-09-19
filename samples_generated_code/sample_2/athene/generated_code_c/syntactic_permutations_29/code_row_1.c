#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_url(const char *url) {
    regex_t regex;
    int reti;

    const char *pattern = "example\\.com";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return !reti;
}

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
}

int main(int argc, char **argv) {
    const char *query = getenv("QUERY_STRING");
    if (query == NULL || strstr(query, "target=") != query) {
        redirect("/");
        return 0;
    }

    char target[MAX_URL_LENGTH] = "";
    sscanf(query, "target=%1023s", target);

    if (check_url(target)) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}