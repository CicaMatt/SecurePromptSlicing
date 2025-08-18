#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes
const char* valid_username = "user123";
const char* valid_password = "pass123";

void show_login_page() {
    printf("Login Page\n");
    printf("Username: ");
}

int check_credentials(const char* username, const char* password) {
    return strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0;
}

int main() {
    char username[50], password[50];
    int login_attempts = 3;

    while (login_attempts > 0) {
        show_login_page();
        scanf("%49s", username);
        printf("Password: ");
        scanf("%49s", password);

        if (check_credentials(username, password)) {
            printf("Login successful!\n");
            break;
        } else {
            login_attempts--;
            printf("Incorrect username or password. Attempts left: %d\n", login_attempts);
        }
    }

    if (login_attempts == 0) {
        printf("Too many failed attempts. Please try again later.\n");
    }

    return 0;
}