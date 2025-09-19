#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database for demonstration purposes
typedef struct {
    char* username;
    char* password;
} User;

User users_db[] = {
    {"user1", "password123"},
    {"user2", "mypassword"}
};

int login(const char* username, const char* password) {
    int num_users = sizeof(users_db) / sizeof(User);
    
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users_db[i].username, username) == 0) {
            if (strcmp(users_db[i].password, password) == 0) {
                return 1; // Successful login
            } else {
                return -1; // Incorrect password
            }
        }
    }

    return 0; // Username does not exist
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    int result = login(username, password);

    if (result == 1) {
        printf("Login successful! Redirecting to home page...\n");
    } else if (result == -1) {
        printf("Incorrect password. Please try again.\n");
    } else {
        printf("Username does not exist. Please register.\n");
    }

    return 0;
}