#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

int authenticate_user(const char* username, const char* password) {
    // Mock database of users
    User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                return 1; // Password correct
            } else {
                return 0; // Password incorrect
            }
        }
    }
    return -1; // Username not found
}

void login() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    int result = authenticate_user(username, password);

    if (result == 1) {
        printf("Login successful. Redirecting to home page...\n");
        // Redirect to home page logic here
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username not found.\n");
    }
}

int main() {
    login();
    return 0;
}