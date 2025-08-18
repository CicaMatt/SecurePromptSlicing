#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    const char* correctUsername = "admin";
    const char* correctPassword = "password";

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        printf("Login successful! Redirecting to session page...\n");
        // Here you would typically redirect to another page or function
    } else {
        printf("Incorrect username or password. Please try again.\n");
    }

    return 0;
}