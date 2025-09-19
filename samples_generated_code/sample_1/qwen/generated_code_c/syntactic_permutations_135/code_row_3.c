#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

bool check_credentials(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void simulate_form_input(char *username, char *password) {
    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character
}

bool check_mod() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    simulate_form_input(username, password);

    return check_credentials(username, password);
}

int main() {
    if (check_mod()) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }

    return 0;
}