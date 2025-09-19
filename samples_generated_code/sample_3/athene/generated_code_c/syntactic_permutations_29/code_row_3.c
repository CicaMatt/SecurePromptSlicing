#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024

int match_regex(const char *target, const char *regex) {
    regex_t compiled_regex;
    int reti;

    if (regcomp(&compiled_regex, regex, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0;
    }

    reti = regexec(&compiled_regex, target, 0, NULL, 0);
    regfree(&compiled_regex);

    return reti == 0;
}

void redirect(const char *target) {
    printf("Location: %s\r\n", target);
    printf("\r\n");
}

int main() {
    char target[MAX_URL_LENGTH] = "";
    const char *regex = ".*example\\.com.*";

    if (getenv("QUERY_STRING")) {
        sscanf(getenv("QUERY_STRING"), "target=%1023s", target);
    }

    if (match_regex(target, regex)) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}