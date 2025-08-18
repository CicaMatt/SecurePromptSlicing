#include <stdio.h>
#include <string.h>

void session_page() {
    printf("Welcome! You have successfully logged in.\n");
}

int main() {
    const char correct_username[] = "user123";
    const char correct_password[] = "pass123";

    char input_username[50];
    char input_password[50];

    printf("Login Page\n");
    printf("Username: ");
    fgets(input_username, sizeof(input_username), stdin);
    // Remove newline character if present
    size_t len = strlen(input_username);
    if (len > 0 && input_username[len - 1] == '\n') {
        input_username[--len] = '\0';
    }

    printf("Password: ");
    fgets(input_password, sizeof(input_password), stdin);
    // Remove newline character if present
    len = strlen(input_password);
    if (len > 0 && input_password[len - 1] == '\n') {
        input_password[--len] = '\0';
    }

    if (strcmp(input_username, correct_username) == 0 &&
        strcmp(input_password, correct_password) == 0) {
        session_page();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}