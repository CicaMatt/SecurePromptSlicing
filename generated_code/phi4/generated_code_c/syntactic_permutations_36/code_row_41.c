#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User users_db[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int user_count = sizeof(users_db) / sizeof(users_db[0]);

// Function to simulate database query for a user by username
int query_user(const char* username, char* password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users_db[i].username, username) == 0) {
            strcpy(password, users_db[i].password);
            return 1;
        }
    }
    return 0;
}

// Function to perform login
void login(const char* username, const char* password) {
    char db_password[50];

    // Query the database for the user
    if (query_user(username, db_password)) {
        printf("Username found.\n");

        // Check if the password is correct
        if (strcmp(password, db_password) == 0) {
            printf("Password correct. Redirecting to home page...\n");
            // Simulate redirection to home page
            system("echo 'Welcome to Home Page!'");
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    // Prompt user for login credentials
    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    // Call the login function
    login(username, password);

    return 0;
}