#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048

void redirect(const char *url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

int matches_regex(const char *str, const char *pattern) {
    regex_t re;
    int ret;

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return -1;
    }

    ret = regexec(&re, str, 0, NULL, 0);
    regfree(&re);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return -1;
    }
}

int main() {
    char target[MAX_URL_LENGTH];
    const char *regex_pattern = "example\\.com";

    printf("Content-Type: text/html\r\n");

    if (fgets(target, MAX_URL_LENGTH, stdin) != NULL) {
        // Simple parsing of the query parameter for demonstration
        char *query_start = strstr(target, "?target=");
        if (query_start != NULL) {
            char *url_start = query_start + strlen("?target=");
            char *end_of_url = strchr(url_start, ' ');
            if (end_of_url != NULL) {
                *end_of_url = '\0';
                if (matches_regex(url_start, regex_pattern) == 1) {
                    redirect(url_start);
                } else {
                    redirect("/");
                }
            }
        }
    }

    return 0;
}