#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    
    const char *valid_username = "admin";
    const char *valid_password = "password123";

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        printf("Login successful! Redirecting to session page...\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}