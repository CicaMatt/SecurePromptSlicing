#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User mockDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int login(char *username, char *password) {
    int size = sizeof(mockDatabase) / sizeof(User);
    
    for (int i = 0; i < size; i++) {
        if (strcmp(username, mockDatabase[i].username) == 0) {
            if (strcmp(password, mockDatabase[i].password) == 0) {
                return 1; // Success
            } else {
                return -1; // Incorrect password
            }
        }
    }

    return 0; // User not found
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
    // Add actual redirection logic here if needed
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    int result = login(username, password);

    if (result == 1) {
        redirectToHomePage();
    } else {
        printf("Invalid credentials.\n");
    }

    return 0;
}