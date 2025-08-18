#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define REGEX ".*example\\.com.*"

void redirect(const char *target) {
    printf("Location: %s\n", target);
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

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || !match_regex(target, REGEX)) {
        redirect("/");
    } else {
        redirect(target);
    }
    return 0;
}