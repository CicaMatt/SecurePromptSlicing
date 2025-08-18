#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password);

int main() {
    char username[50], password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (check_mod(username, password)) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}

int check_mod(const char *username, const char *password) {
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}