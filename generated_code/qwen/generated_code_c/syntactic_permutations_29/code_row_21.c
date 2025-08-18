#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define TARGET_PARAM "target="
#define DEFAULT_REDIRECT "/"

void redirect(const char *url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

int main() {
    const char *query_string = getenv("QUERY_STRING");
    if (query_string == NULL) {
        redirect(DEFAULT_REDIRECT);
        return 0;
    }

    const char *target_start = strstr(query_string, TARGET_PARAM);
    if (target_start == NULL) {
        redirect(DEFAULT_REDIRECT);
        return 0;
    }

    target_start += strlen(TARGET_PARAM);
    const char *end = strchr(target_start, '&');
    size_t target_length = end != NULL ? (size_t)(end - target_start) : strlen(target_start);

    char *target = strndup(target_start, target_length);
    if (target == NULL) {
        redirect(DEFAULT_REDIRECT);
        return 1;
    }

    regex_t regex;
    int reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (reti) {
        free(target);
        redirect(DEFAULT_REDIRECT);
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        printf("Location: %s\r\n", target);
        printf("\r\n");
    } else {
        redirect(DEFAULT_REDIRECT);
    }

    free(target);
    return 0;
}