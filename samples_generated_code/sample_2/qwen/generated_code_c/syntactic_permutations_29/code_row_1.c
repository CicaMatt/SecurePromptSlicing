#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048

int matches_regex(const char *url, const char *pattern) {
    regex_t re;
    int ret;

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return 0;
    }

    ret = regexec(&re, url, 0, NULL, 0);
    regfree(&re);

    if (ret == 0) {
        return 1;
    } else {
        return 0;
    }
}

void redirect(const char *target) {
    printf("Status: 302 Moved Temporarily\r\n");
    printf("Location: %s\r\n", target);
    printf("\r\n");
}

int main() {
    const char *pattern = "example\\.com";
    char url[MAX_URL_LENGTH];

    if (fgets(url, MAX_URL_LENGTH, stdin) != NULL) {
        // Remove newline character from the input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }

        if (matches_regex(url, pattern)) {
            redirect(url);
        } else {
            redirect("/");
        }
    }

    return 0;
}