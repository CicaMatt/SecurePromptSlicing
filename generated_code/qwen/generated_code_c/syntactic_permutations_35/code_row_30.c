#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

int authenticate(const char *username, const char *password) {
    // This is a simple static check for demonstration purposes.
    // In a real application, you would query a database here.
    User validUser = {"admin", "password123"};
    return strcmp(username, validUser.username) == 0 && strcmp(password, validUser.password) == 0;
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would use HTTP redirection here.
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // In a real web application, you would use HTTP redirection here.
    }

    return 0;
}