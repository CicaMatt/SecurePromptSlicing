#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool authenticate(const char* username, const char* password) {
    const char* validUsername = "admin";
    const char* validPassword = "password123";

    if (strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Authentication successful.\n");
    } else {
        printf("Authentication failed.\n");
    }

    return 0;
}