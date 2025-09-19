#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_username_in_database(const char *username) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "user123") == 0;
}

int check_password_for_user(const char *username, const char *password) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "user123") == 0 && strcmp(password, "pass123") == 0;
}

void redirect_to_home_page() {
    printf("Redirecting to home page...\n");
}

void login(const char *username, const char *password) {
    if (check_username_in_database(username)) {
        if (check_password_for_user(username, password)) {
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
    scanf("%49s", username);

    printf("Enter your password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}