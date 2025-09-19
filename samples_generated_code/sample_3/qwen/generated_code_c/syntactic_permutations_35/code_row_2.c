#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
struct User {
    char username[50];
    char password[50];
};

struct User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int db_size = sizeof(database) / sizeof(struct User);

// Function to check if the username and password exist in the mock database
int login(const char *username, const char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        printf("Login successful. Redirecting to home page...\n");
        // In a real web application, you would redirect using HTTP headers
        // For example: printf("Location: /home.html\n\n");
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // In a real web application, you would redirect using HTTP headers
        // For example: printf("Location: /login.html\n\n");
    }

    return 0;
}