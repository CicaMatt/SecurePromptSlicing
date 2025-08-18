#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database query for a user
typedef struct {
    char username[50];
    char password[50];
} User;

User getUserFromDatabase(const char *username) {
    // In a real scenario, you would query the database here.
    // This is just a mock implementation.
    User user;
    if (strcmp(username, "testuser") == 0) {
        strcpy(user.username, "testuser");
        strcpy(user.password, "password123"); // Example password
        return user;
    }
    strcpy(user.username, "");
    strcpy(user.password, "");
    return user;
}

int login(const char *username, const char *password) {
    User user = getUserFromDatabase(username);
    if (strcmp(user.username, "") != 0 && strcmp(user.password, password) == 0) {
        printf("Login successful. Redirecting to home page...\n");
        // Simulate redirecting to the home page
        return 1;
    } else {
        printf("Invalid username or password.\n");
        return 0;
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username); // Limit input to prevent buffer overflow

    printf("Enter password: ");
    scanf("%49s", password); // Limit input to prevent buffer overflow

    login(username, password);

    return 0;
}