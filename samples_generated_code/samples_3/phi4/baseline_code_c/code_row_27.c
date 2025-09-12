#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    // Hardcoded credentials for demonstration purposes.
    const char *correct_username = "user";
    const char *correct_password = "pass";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}

int main() {
    char username[50];
    char password[50];

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