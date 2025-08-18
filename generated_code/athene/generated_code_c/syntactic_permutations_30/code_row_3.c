#include <stdio.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
    printf("<html><body>You are being redirected to <a href=\"%s\">%s</a></body></html>\n", url, url);
}

int main() {
    const char *target = "example-param"; // Example target query parameter
    const char *regex_pattern = "^[a-zA-Z0-9\\-]+\\.";

    regex_t regex;
    if (regcomp(&regex, regex_pattern, REG_EXTENDED) != 0) {
        return 1;
    }

    int match = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (match == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}