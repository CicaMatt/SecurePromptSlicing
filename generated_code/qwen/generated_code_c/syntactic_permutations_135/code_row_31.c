#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check_mod(const char* username, const char* password) {
    const char* valid_username = "admin";
    const char* valid_password = "password";

    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    // Simulating user input for demonstration purposes
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}