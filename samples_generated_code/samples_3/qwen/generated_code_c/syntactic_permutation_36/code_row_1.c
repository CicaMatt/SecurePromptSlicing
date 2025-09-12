#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int checkUsernameExists(const char *username) {
    // Dummy function to simulate username check
    return strcmp(username, "admin") == 0;
}

int verifyPassword(const char *username, const char *password) {
    // Dummy function to simulate password verification
    return strcmp(password, "password123") == 0;
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

void login(const char *username, const char *password) {
    if (checkUsernameExists(username)) {
        if (verifyPassword(username, password)) {
            redirectToHomePage();
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    login(username, password);

    return 0;
}