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
    const char *query = getenv("QUERY_STRING");
    if (query == NULL) {
        redirect("/");
    }

    const char *target = "target=";
    size_t target_len = strlen(target);
    const char *start = strstr(query, target);
    if (start == NULL) {
        redirect("/");
    }
    start += target_len;

    const char *regex_str = "^[a-zA-Z0-9\\-]+\\.";
    regex_t regex;
    int reti = regcomp(&regex, regex_str, REG_EXTENDED | REG_NOSUB);
    if (reti) {
        redirect("/");
    }

    if (regexec(&regex, start, 0, NULL, 0) == 0) {
        redirect(start);
    } else {
        redirect("/");
    }

    regfree(&regex);
    return 0;
}