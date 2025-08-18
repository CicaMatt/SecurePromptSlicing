#include <stdio.h>
#include <string.h>

void login_page() {
    char stored_username[] = "user123";
    char stored_password[] = "pass456";

    char input_username[50];
    char input_password[50];

    printf("Login Page\n");
    printf("Enter username: ");
    fgets(input_username, sizeof(input_username), stdin);
    input_username[strcspn(input_username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = 0; // Remove newline character

    if (strcmp(input_username, stored_username) == 0 && strcmp(input_password, stored_password) == 0) {
        printf("Login successful! Redirecting to session page...\n");
        session_page();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void session_page() {
    printf("Welcome to the session page!\n");
    // Session code here
}

int main() {
    login_page();
    return 0;
}