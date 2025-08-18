#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define REGEX "example\\.com"

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int match_regex(const char *target, const char *regex) {
    regex_t compiled;
    int ret;

    if (regcomp(&compiled, regex, REG_EXTENDED) != 0) {
        return 0;
    }

    ret = regexec(&compiled, target, 0, NULL, 0);
    regfree(&compiled);

    return ret == 0;
}

void handle_request(const char *target) {
    if (match_regex(target, REGEX)) {
        redirect(target);
    } else {
        redirect("/");
    }
}

int main() {
    const char *target = getenv("QUERY_STRING");
    if (target != NULL && strstr(target, "target=") == target) {
        target += strlen("target=");
        handle_request(target);
    } else {
        redirect("/");
    }

    return 0;
}