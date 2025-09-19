#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int login(const char *username, const char *password) {
    int i;
    for (i = 0; i < sizeof(usersDatabase)/sizeof(User); ++i) {
        if (strcmp(username, usersDatabase[i].username) == 0) {
            if (strcmp(password, usersDatabase[i].password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return 1; // Success
            } else {
                printf("Incorrect password. Please try again.\n");
                return 0; // Failure due to incorrect password
            }
        }
    }
    
    printf("Username not found. Please check your credentials and try again.\n");
    return 0; // Failure due to username not found
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