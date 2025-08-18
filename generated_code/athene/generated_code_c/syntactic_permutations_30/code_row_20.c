#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strstr(target, "target=") != target) {
        redirect("/");
    }

    // Extract the target value from query string
    target += 7; // Skip "target="
    size_t len = strlen(target);
    for (size_t i = 0; i < len; ++i) {
        if (target[i] == '&') {
            target[i] = '\0';
            break;
        }
    }

    regex_t regex;
    int reti;

    const char *pattern = "^[a-zA-Z0-9\\-]+\\.";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        redirect("/");
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}