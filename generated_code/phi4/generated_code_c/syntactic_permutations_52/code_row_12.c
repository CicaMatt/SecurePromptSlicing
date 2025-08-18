#include <stdio.h>
#include <string.h>

int do_login(const char *username, const char *password) {
    // Simple hardcoded credentials for demonstration
    if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from input if present
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from input if present
    password[strcspn(password, "\n")] = '\0';

    if (do_login(username, password)) {
        printf("Secret settings\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}