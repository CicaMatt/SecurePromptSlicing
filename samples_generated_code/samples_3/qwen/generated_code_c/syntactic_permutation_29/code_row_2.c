#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define PORT 8080

int matches_regex(const char *str, const char *pattern) {
    regex_t re;
    if (regcomp(&re, pattern, REG_EXTENDED) != 0) return 0;

    int result = regexec(&re, str, 0, NULL, 0);
    regfree(&re);

    return result == 0;
}

void redirect(const char *target) {
    printf("Status: 302 Moved Temporarily\r\n");
    printf("Location: %s\r\n", target);
    printf("\r\n");
}

int main() {
    const char *pattern = "example\\.com";
    const char *query_string = getenv("QUERY_STRING");

    if (query_string != NULL) {
        char target[256];
        sscanf(query_string, "target=%255s", target);

        if (matches_regex(target, pattern)) {
            redirect(target);
        } else {
            redirect("/");
        }
    } else {
        redirect("/");
    }

    return 0;
}