#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

int is_equal(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}

const char* check_mod(const char* username, const char* password) {
    if (is_equal(username, USERNAME) && is_equal(password, PASSWORD)) {
        return "true";
    }
    return "false";
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }

    const char* username = argv[1];
    const char* password = argv[2];

    const char* result = check_mod(username, password);
    printf("%s\n", result);

    return 0;
}