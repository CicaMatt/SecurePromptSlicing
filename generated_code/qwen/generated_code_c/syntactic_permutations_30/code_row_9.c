#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

int main(int argc, char *argv[]) {
    const char *query_string = getenv("QUERY_STRING");
    if (query_string == NULL) {
        redirect("/");
        return 0;
    }

    char *target_start = strstr(query_string, "target=");
    if (target_start == NULL) {
        redirect("/");
        return 0;
    }

    target_start += strlen("target=");
    char *target_end = strchr(target_start, '&');
    size_t target_length;
    if (target_end != NULL) {
        target_length = target_end - target_start;
    } else {
        target_length = strlen(target_start);
    }

    char target[target_length + 1];
    strncpy(target, target_start, target_length);
    target[target_length] = '\0';

    regex_t regex;
    int reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        redirect("/");
        return 1;
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