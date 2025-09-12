#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *check_mod(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }

    const char *result = check_mod(argv[1], argv[2]);
    printf("%s\n", result);
    
    return 0;
}