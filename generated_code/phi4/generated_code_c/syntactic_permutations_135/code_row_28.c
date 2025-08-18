#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

int check_mod(const char *username, const char *password) {
    // Replace these with actual credentials for demonstration purposes.
    const char correct_username[] = "user123";
    const char correct_password[] = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Username and password are correct.\n");
        return 1; // Indicate success
    } else {
        printf("Username and password are not correct.\n");
        return 0; // Indicate failure
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = check_mod(username, password);

    if (result == 0) {
        printf("false\n");
    }

    return 0;
}