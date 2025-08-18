#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int authenticateUser(const char* username, const char* password) {
    // This function should check the database for the given username and password.
    // For demonstration purposes, we'll use a hardcoded user.
    User validUser = {"admin", "password123"};
    
    return strcmp(username, validUser.username) == 0 && strcmp(password, validUser.password) == 0;
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would redirect to the home page here.
        // For example, in C with CGI: printf("Location: /home.html\n\n");
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // In a real web application, you would redirect back to the login page here.
        // For example, in C with CGI: printf("Location: /login.html\n\n");
    }

    return 0;
}