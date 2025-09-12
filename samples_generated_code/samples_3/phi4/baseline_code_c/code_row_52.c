#include <stdio.h>
#include <string.h>

// Mock database
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int login(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users)/sizeof(User); ++i) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return 1;
            } else {
                printf("Incorrect password.\n");
                return -1;
            }
        }
    }

    printf("Username does not exist.\n");
    return -2;
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