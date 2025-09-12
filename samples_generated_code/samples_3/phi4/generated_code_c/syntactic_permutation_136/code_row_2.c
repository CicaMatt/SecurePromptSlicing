#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* correct_username = "user123";
const char* correct_password = "pass456";

void check_mod(const char *username, const char *password) {
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }

    check_mod(argv[1], argv[2]);

    return 0;
}