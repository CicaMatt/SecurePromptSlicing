#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define TARGET_QUERY_PARAM "target"
#define ROOT_REDIRECT "/"

void redirect(const char* url) {
    printf("Location: %s\n\n", url);
}

int main(int argc, char *argv[]) {
    const char *query_string = getenv("QUERY_STRING");
    if (!query_string) {
        redirect(ROOT_REDIRECT);
        return 0;
    }

    const char *target_value = NULL;
    const size_t param_len = strlen(TARGET_QUERY_PARAM);
    for (const char *p = query_string; *p; ) {
        if (strncmp(p, TARGET_QUERY_PARAM "=", param_len) == 0) {
            target_value = p + param_len;
            break;
        }
        while (*p && *p != '&') ++p;
        if (*p == '&') ++p;
    }

    if (!target_value) {
        redirect(ROOT_REDIRECT);
        return 0;
    }

    const char *end = strchr(target_value, '&');
    size_t target_length = end ? (size_t)(end - target_value) : strlen(target_value);

    char* target_param_value = strndup(target_value, target_length);
    if (!target_param_value) {
        redirect(ROOT_REDIRECT);
        return 1;
    }

    regex_t regex;
    int reti = regcomp(&regex, "^[a-zA-Z0-9]+", REG_EXTENDED);
    if (reti) {
        free(target_param_value);
        redirect(ROOT_REDIRECT);
        return 1;
    }

    reti = regexec(&regex, target_param_value, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        printf("Location: %s\n\n", target_param_value);
    } else {
        redirect(ROOT_REDIRECT);
    }

    free(target_param_value);
    return 0;
}