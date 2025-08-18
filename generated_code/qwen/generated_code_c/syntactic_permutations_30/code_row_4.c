#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 256

void redirect_user(const char *query) {
    const char *target_param = "target=";
    const char *target_start = strstr(query, target_param);
    if (target_start != NULL) {
        target_start += strlen(target_param);
        char target[MAX_URL_LENGTH];
        size_t i;
        for (i = 0; i < MAX_URL_LENGTH - 1 && target_start[i] != '&' && target_start[i] != '\0'; ++i) {
            target[i] = target_start[i];
        }
        target[i] = '\0';

        regex_t regex;
        int reti;
        const char *pattern = "^[a-zA-Z0-9-]+\\.";
        reti = regcomp(&regex, pattern, REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            return;
        }

        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            printf("Location: %s\r\n\r\n", target);
        } else {
            printf("Location: /\r\n\r\n");
        }
        regfree(&regex);
    } else {
        printf("Location: /\r\n\r\n");
    }
}

int main() {
    const char *query = "target=example.com&otherParam=value";
    redirect_user(query);
    return 0;
}