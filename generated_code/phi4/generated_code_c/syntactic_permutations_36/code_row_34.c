#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure for demonstration purposes.
typedef struct {
    char username[50];
    char password[50];
} User;

// Example users in a "database"
User userDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int login(char *username, char *password) {
    int numUsers = sizeof(userDatabase) / sizeof(User);
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(userDatabase[i].username, username) == 0) {
            if (strcmp(userDatabase[i].password, password) == 0) {
                printf("Login successful!\n");
                return 1;
            } else {
                printf("Incorrect password.\n");
                return 0;
            }
        }
    }
    printf("Username does not exist.\n");
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}