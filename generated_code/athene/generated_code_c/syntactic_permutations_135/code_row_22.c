#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "12345";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}

int main() {
    const char *input_username = "admin";
    const char *input_password = "12345";

    if (check_mod(input_username, input_password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }

    return 0;
}