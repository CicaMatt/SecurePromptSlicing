#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes.
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password123"},
    {"user2", "pass456"}
};

int login(const char *username, const char *password) {
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0) {
            if (strcmp(password, users[i].password) == 0) {
                printf("Login successful!\nRedirecting to home page...\n");
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