#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100

int check_mod(const char *username, const char *password) {
    // Example credentials for demonstration purposes
    const char correct_username[] = "user123";
    const char correct_password[] = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LEN, stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0'; // Remove newline character
    }

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LEN, stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0'; // Remove newline character
    }

    int result = check_mod(username, password);
    if (result) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}