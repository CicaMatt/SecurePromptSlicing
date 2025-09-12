#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    const char *pattern = "example\\.com";
    char regexPattern[] = ".*" pattern ".*";

    if (strstr(target, pattern)) {
        printf("Redirecting to: %s\n", target);
        // In a real web application, you would use an actual redirect function here.
        // For example purposes, we just print the redirection.
    } else {
        printf("Redirecting to: /\n");
        // Similarly, this is where a redirect to "/" would occur.
    }

    return 0;
}