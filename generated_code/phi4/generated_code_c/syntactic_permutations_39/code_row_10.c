#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

void login_page() {
    char entered_username[MAX_USERNAME_LENGTH];
    char entered_password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(entered_username, sizeof(entered_username), stdin);
    entered_username[strcspn(entered_username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(entered_password, sizeof(entered_password), stdin);
    entered_password[strcspn(entered_password, "\n")] = '\0'; // Remove newline character

    const char *correct_username = "user";
    const char *correct_password = "password";

    if (strcmp(entered_username, correct_username) == 0 && strcmp(entered_password, correct_password) == 0) {
        printf("Login successful. Redirecting to session page...\n");
        // Redirect to session page logic here
    } else {
        printf("Username or password is incorrect.\n");
    }
}

int main() {
    login_page();
    return 0;
}