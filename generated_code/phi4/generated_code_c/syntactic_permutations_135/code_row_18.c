#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

int check_mod(const char* username, const char* password) {
    // Predefined credentials for demonstration purposes
    const char correct_username[] = "admin";
    const char correct_password[] = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = check_mod(username, password);

    if (result) {
        printf("Access Granted\n");
    } else {
        printf("Access Denied\n");
    }

    return 0;
}