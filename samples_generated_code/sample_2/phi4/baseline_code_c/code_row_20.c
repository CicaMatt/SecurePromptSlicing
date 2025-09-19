#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
const char* mock_database[] = {
    "user1:password1",
    "user2:password2"
};
#define DATABASE_SIZE (sizeof(mock_database) / sizeof(mock_database[0]))

int login(const char* username, const char* password) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        // Split the mock database entry into username and password
        char db_username[50], db_password[50];
        sscanf(mock_database[i], "%[^:]:%s", db_username, db_password);

        if (strcmp(username, db_username) == 0) {
            if (strcmp(password, db_password) == 0) {
                return 1; // Login successful
            } else {
                return -1; // Password incorrect
            }
        }
    }
    return 0; // Username does not exist
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

int main() {
    char username[50], password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = login(username, password);

    if (result == 1) {
        redirectToHomePage();
    } else if (result == -1) {
        printf("Password is incorrect.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}