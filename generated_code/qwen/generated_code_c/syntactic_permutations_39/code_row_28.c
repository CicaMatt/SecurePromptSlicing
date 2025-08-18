#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    const char *correctName = "admin";
    const char *correctPassword = "password123";

    printf("Enter your name: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    // Remove newline character from the input
    name[strcspn(name, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character from the input
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(name, correctName) == 0 && strcmp(password, correctPassword) == 0) {
        printf("Login successful! Redirecting to session page...\n");
    } else {
        printf("Incorrect name or password.\n");
    }

    return 0;
}