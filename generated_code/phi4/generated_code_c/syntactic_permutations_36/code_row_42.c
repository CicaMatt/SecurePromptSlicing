#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock database structure for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

#define USER_COUNT (sizeof(users) / sizeof(users[0]))

int login(const char *username, const char *password) {
    for (int i = 0; i < USER_COUNT; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return 1;
            } else {
                printf("Incorrect password. Please try again.\n");
                return 0;
            }
        }
    }
    
    printf("Username does not exist. Please register or check your username.\n");
    return 0;
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