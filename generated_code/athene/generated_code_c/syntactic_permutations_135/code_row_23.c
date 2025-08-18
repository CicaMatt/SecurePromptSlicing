#include <stdio.h>
#include <string.h>

int check_mod(const char* username, const char* password) {
    const char *correct_username = "admin";
    const char *correct_password = "12345";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}

int main() {
    const char* username = "admin";
    const char* password = "12345";

    if (check_mod(username, password)) {
        printf("Credentials are correct.\n");
    } else {
        printf("Credentials are incorrect.\n");
    }

    return 0;
}