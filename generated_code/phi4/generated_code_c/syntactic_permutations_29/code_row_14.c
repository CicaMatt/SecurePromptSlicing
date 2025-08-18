#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TARGET_LENGTH 256

int matches_regex(const char *target) {
    return strstr(target, "example.com") != NULL;
}

void redirect(const char *url) {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

void handle_request(char *target) {
    if (matches_regex(target)) {
        redirect("/success");
    } else {
        redirect("/");
    }
}

int main() {
    char target[MAX_TARGET_LENGTH];
    
    printf("Enter target URL: ");
    fgets(target, MAX_TARGET_LENGTH, stdin);
    target[strcspn(target, "\n")] = '\0'; // Remove newline character

    handle_request(target);

    return 0;
}