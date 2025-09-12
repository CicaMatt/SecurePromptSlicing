#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* username, const char* password) {
    // This is a simple in-memory check. In a real application, you would query a database.
    User validUser = {"admin", "password123"};
    return strcmp(username, validUser.username) == 0 && strcmp(password, validUser.password) == 0;
}

void handleLogin(const char* username, const char* password) {
    if (authenticateUser(username, password)) {
        printf("Location: home.html\r\n\r\n");
    } else {
        printf("Location: login.html\r\n\r\n");
    }
}

int main() {
    // Simulating form data input
    const char* username = "admin";
    const char* password = "password123";

    // Set the content type to text/html for CGI output
    printf("Content-Type: text/html\r\n\r\n");

    handleLogin(username, password);

    return 0;
}