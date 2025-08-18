#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

void login_page() {
    char stored_username[MAX_INPUT_LENGTH] = "user";
    char stored_password[MAX_INPUT_LENGTH] = "password";

    char input_username[MAX_INPUT_LENGTH];
    char input_password[MAX_INPUT_LENGTH];

    printf("Enter username: ");
    fgets(input_username, sizeof(input_username), stdin);
    // Remove newline character from username
    input_username[strcspn(input_username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(input_password, sizeof(input_password), stdin);
    // Remove newline character from password
    input_password[strcspn(input_password, "\n")] = '\0';

    if (strcmp(input_username, stored_username) == 0 && strcmp(input_password, stored_password) == 0) {
        printf("Login successful! Redirecting to session page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    login_page();
    return 0;
}