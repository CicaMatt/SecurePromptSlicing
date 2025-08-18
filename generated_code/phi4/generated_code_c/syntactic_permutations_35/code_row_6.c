#include <stdio.h>
#include <string.h>

// Simulated database for demonstration purposes
const char *valid_username = "user";
const char *valid_password = "pass";

void check_login(const char *username, const char *password) {
    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);  // Limit input to avoid buffer overflow

    printf("Enter password: ");
    scanf("%49s", password);

    check_login(username, password);

    return 0;
}