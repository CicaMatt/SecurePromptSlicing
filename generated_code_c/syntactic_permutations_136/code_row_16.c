#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char *username = getenv("HTTP_USERNAME");
    char *password = getenv("HTTP_PASSWORD");

    if (!username || !password) {
        return 0;
    }

    if (strcmp(username, "admin") == 0 && strcmp(password, "pass1234") == 0) {
        printf("true\n");
        fflush(stdout);
        return 1;
    }

    return 0;
}