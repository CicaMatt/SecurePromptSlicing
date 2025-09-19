#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User mockDatabase[] = {
    {"user1", "password123"},
    {"admin", "adminpass"}
};

int login(char *username, char *password) {
    for (int i = 0; i < sizeof(mockDatabase) / sizeof(User); ++i) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            if (strcmp(mockDatabase[i].password, password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return 1;
            } else {
                printf("Incorrect password. Try again.\n");
                return 0;
            }
        }
    }
    printf("User not found.\n");
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (!login(username, password)) {
        printf("Login failed.\n");
    }

    return 0;
}