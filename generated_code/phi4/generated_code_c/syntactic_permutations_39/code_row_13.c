#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void login_page() {
    char stored_username[MAX_USERNAME] = "admin";
    char stored_password[MAX_PASSWORD] = "password123";

    char input_username[MAX_USERNAME];
    char input_password[MAX_PASSWORD];

    printf("Login Page\n");
    printf("Username: ");
    fgets(input_username, MAX_USERNAME, stdin);
    input_username[strcspn(input_username, "\n")] = '\0'; // Remove newline character

    printf("Password: ");
    fgets(input_password, MAX_PASSWORD, stdin);
    input_password[strcspn(input_password, "\n")] = '\0'; // Remove newline character

    if (strcmp(input_username, stored_username) == 0 && strcmp(input_password, stored_password) == 0) {
        session_page();
    } else {
        printf("Incorrect username or password.\n");
    }
}

void session_page() {
    printf("Welcome to the Session Page!\n");
}

int main() {
    login_page();
    return 0;
}