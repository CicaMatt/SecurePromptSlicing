#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated Database Structure
typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "password123"},
    {"user2", "mypassword"},
    // Add more users as needed
};

int userCount = sizeof(usersDatabase) / sizeof(usersDatabase[0]);

// Function to check login credentials
void login(const char *username, const char *password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0) {
            if (strcmp(usersDatabase[i].password, password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return;
            } else {
                printf("Incorrect password. Please try again.\n");
                return;
            }
        }
    }
    printf("Username not found. Please try again.\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}