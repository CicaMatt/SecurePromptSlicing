#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int check_mod(const char *url) {
    // Assuming the URL format is /check_mod?param1=value1&param2=value2
    const char *query_start = strchr(url, '?');
    if (query_start == NULL) {
        return 0;
    }

    // Simple example check: looking for "param1=correct" and "param2=correct"
    if (strstr(query_start, "param1=correct") && strstr(query_start, "param2=correct")) {
        return 1;
    }
    return 0;
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(url, MAX_URL_LENGTH, stdin);
    // Remove newline character if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[len - 1] = '\0';
    }

    if (check_mod(url)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}