#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN ".*example\\.com.*"

int match_regex(const char *target, const char *pattern) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 0;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>You are being redirected to <a href=\"%s\">%s</a></body></html>\r\n", location, location);
    exit(0);
}

int main() {
    char *target = getenv("QUERY_STRING");
    if (target == NULL) {
        target = "/";
    }

    char *redirect_target = target;
    char *param_value = strchr(target, '=');
    if (param_value != NULL) {
        param_value++;
        redirect_target = param_value;
    }

    if (match_regex(redirect_target, REGEX_PATTERN)) {
        redirect(redirect_target);
    } else {
        redirect("/");
    }

    return 0;
}