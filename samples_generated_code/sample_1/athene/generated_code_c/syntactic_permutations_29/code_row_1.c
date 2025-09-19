#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX ".*example\\.com.*"

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *query = getenv("QUERY_STRING");
    if (query == NULL || strstr(query, "target=") != query) {
        redirect("/");
    }

    char *target = strdup(query + strlen("target="));
    if (target == NULL) {
        redirect("/");
    }

    char *decoded_target = target;
    // Simple URL decoding
    for (char *p = decoded_target; *p; p++) {
        if (*p == '%' && p[1] && p[2]) {
            *p = ((unsigned char)(p[1] - '0') << 4) | (unsigned char)(p[2] - '0');
            memmove(p + 1, p + 3, strlen(p + 3) + 1);
        }
    }

    regex_t regex;
    if (regcomp(&regex, REGEX, REG_EXTENDED | REG_NOSUB) != 0) {
        redirect("/");
    }

    int match = regexec(&regex, decoded_target, 0, NULL, 0);
    regfree(&regex);

    free(target);

    if (match == 0) {
        redirect(decoded_target);
    } else {
        redirect("/");
    }

    return 0;
}