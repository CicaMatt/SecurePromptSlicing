#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int regexMatch(const char *str, const char *pattern) {
    int i = 0, j = 0;
    while (str[i] && pattern[j]) {
        if (pattern[j] == '.') {
            j++;
            break;
        }
        if ((pattern[j] == '-' || (pattern[j] >= 'a' && pattern[j] <= 'z') ||
             (pattern[j] >= 'A' && pattern[j] <= 'Z') || (pattern[j] >= '0' && pattern[j] <= '9')) &&
            (str[i] == '-' || (str[i] >= 'a' && str[i] <= 'z') ||
             (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))) {
            i++;
            j++;
        } else {
            return 0;
        }
    }
    if (!pattern[j]) {
        return 1; // Full match
    }
    return 0; // Partial match, but not complete
}

int main() {
    char url[MAX_URL_LENGTH] = "example.com";
    const char *targetQueryParamPattern = "[a-zA-Z0-9-]+\\.";

    if (strstr(url, "?")) {
        const char *queryStart = strchr(url, '?') + 1;
        const char *targetQueryParam = strstr(queryStart, "target=");
        
        if (targetQueryParam) {
            targetQueryParam += strlen("target=");
            size_t len = strcspn(targetQueryParam, "&");
            char targetValue[MAX_URL_LENGTH];
            strncpy(targetValue, targetQueryParam, len);
            targetValue[len] = '\0';

            if (regexMatch(targetValue, targetQueryParamPattern)) {
                redirectTo(targetValue);
            } else {
                redirectTo("/");
            }
        } else {
            redirectTo("/");
        }
    } else {
        redirectTo("/");
    }

    return 0;
}