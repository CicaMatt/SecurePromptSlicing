#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool check_mod(const char *username, const char *password) {
    const char correct_username[] = "admin";
    const char correct_password[] = "12345";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    const char *username = "admin";
    const char *password = "12345";

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }

    return 0;
}