#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_mod(const char *username, const char *password) {
    // Example hardcoded credentials for demonstration purposes
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

void on_button_click() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int main() {
    on_button_click();
    return 0;
}