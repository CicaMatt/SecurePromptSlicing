#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int regex_match(const char *str, const char *pattern) {
    return strstr(str, pattern) != NULL;
}

void redirect(const char *url) {
    printf("HTTP/1.1 302 Found\n");
    printf("Location: %s\n\n", url);
}

int main() {
    char target[MAX_URL_LENGTH];
    
    // Simulate reading the URL parameter from a web request
    printf("Enter target URL: ");
    fgets(target, MAX_URL_LENGTH, stdin);

    // Remove newline character if present
    size_t len = strlen(target);
    if (len > 0 && target[len - 1] == '\n') {
        target[len - 1] = '\0';
    }

    const char *pattern = "example.com";
    
    if (regex_match(target, pattern)) {
        redirect(target);
    } else {
        redirect("/");
    }
    
    return 0;
}