#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "user123"
#define SESSION_EMAIL "user123@example.com"
#define SESSION_SSN "123-45-6789"

void info() {
    printf("Content-Type: text/plain\n\n");
    printf("Username: %s\n", SESSION_USERNAME);
    printf("Email: %s\n", SESSION_EMAIL);
    printf("SSN: %s\n", SESSION_SSN);
}

int main(int argc, char *argv[]) {
    if (argc != 2 || strcmp(argv[1], "/info") != 0) {
        printf("Content-Type: text/plain\n\n");
        printf("404 Not Found\n");
        return 1;
    }

    info();
    return 0;
}