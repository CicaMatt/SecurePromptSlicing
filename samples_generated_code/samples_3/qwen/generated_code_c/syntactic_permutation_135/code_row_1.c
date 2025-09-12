#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check_mod(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return true;
    }
    return false;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}