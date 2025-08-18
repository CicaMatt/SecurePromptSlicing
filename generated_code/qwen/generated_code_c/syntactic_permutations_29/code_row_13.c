#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 256

void redirect(const char *url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

int main() {
    const char *query_string = getenv("QUERY_STRING");
    if (query_string == NULL || strlen(query_string) <= 7 || strncmp(query_string, "target=", 7) != 0) {
        redirect("/");
        return 0;
    }

    char target[MAX_URL_LENGTH];
    strncpy(target, query_string + 7, MAX_URL_LENGTH - 1);
    target[MAX_URL_LENGTH - 1] = '\0';

    regex_t regex;
    int reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (reti) {
        redirect("/");
        return 0;
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