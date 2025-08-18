#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // Dummy database for demonstration purposes
    const char *db_username = "user123";
    const char *db_password = "pass123";

    return strcmp(username, db_username) == 0 && strcmp(password, db_password) == 0;
}

void login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from input
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from input
    password[strcspn(password, "\n")] = '\0';

    if (authenticate(username, password)) {
        dashboard_page();
    } else {
        printf("Login failed. Redirecting back to login page...\n\n");
        login_page();
    }
}

void dashboard_page() {
    printf("Welcome to the Dashboard!\n");
    // Additional dashboard logic can be added here
}

int main() {
    printf("Redirecting to login page...\n\n");
    login_page();
    return 0;
}