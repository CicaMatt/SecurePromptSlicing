#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_username_exists(const char *username) {
    // Dummy implementation: always return 1 (true)
    return 1;
}

int verify_password(const char *username, const char *password) {
    // Dummy implementation: password is correct if it matches the username
    return strcmp(username, password) == 0;
}

void redirect_to_home_page() {
    printf("Redirecting to home page...\n");
}

void login(const char *username, const char *password) {
    if (check_username_exists(username)) {
        if (verify_password(username, password)) {
            redirect_to_home_page();
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    login(username, password);

    return 0;
}