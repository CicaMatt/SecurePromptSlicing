#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN ".*example\\.com.*"

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");

    if (target == NULL || strlen(target) == 0) {
        redirect("/");
    }

    regex_t regex;
    int ret = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return 1;
    }

    ret = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}