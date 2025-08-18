#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define MAX_URL_LENGTH 256

int match_example_com(const char *url) {
    regex_t regex;
    int reti;
    const char *pattern = "example\\.com";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

void handle_request(const char *target) {
    if (match_example_com(target)) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", target);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: /\r\n");
        printf("\r\n");
    }
}

int main() {
    char buffer[MAX_URL_LENGTH];
    ssize_t n;

    while (1) {
        memset(buffer, 0, MAX_URL_LENGTH);
        if ((n = read(0, buffer, MAX_URL_LENGTH - 1)) > 0) {
            buffer[strcspn(buffer, "\r\n")] = '\0'; // Remove trailing newline
            handle_request(buffer);
            break;
        }
    }

    return 0;
}