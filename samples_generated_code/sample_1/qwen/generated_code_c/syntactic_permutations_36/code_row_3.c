#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simulated database of users and passwords
typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int db_size = 2;

int login(const char* entered_username, const char* entered_password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, entered_username) == 0) {
            if (strcmp(database[i].password, entered_password) == 0) {
                return 1; // Password correct
            } else {
                return 0; // Incorrect password
            }
        }
    }
    return -1; // Username not found
}

int main() {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%49s", username);
    printf("Enter your password: ");
    scanf("%49s", password);

    int result = login(username, password);

    if (result == 1) {
        printf("Login successful! Redirecting to home page...\n");
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username not found.\n");
    }

    return 0;
}