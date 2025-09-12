#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("\r\n");
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) == 0) {
        target = "target=";
    }
    char *token = strtok((char *)target, "=");
    token = strtok(NULL, "=");

    regex_t regex;
    int reti;
    const char *pattern = ".*example\\.com.*";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        redirect("/");
        return 1;
    }

    reti = regexec(&regex, token, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        redirect(token);
    } else {
        redirect("/");
    }
    return 0;
}