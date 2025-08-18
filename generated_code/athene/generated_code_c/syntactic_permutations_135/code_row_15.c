#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    const char correct_username[] = "admin";
    const char correct_password[] = "123456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *username = "admin";
    const char *password = "123456";

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}