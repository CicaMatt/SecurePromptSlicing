#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int userCount = 2; // Number of users in the database

void login(const char* username, const char* password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 &&
            strcmp(usersDatabase[i].password, password) == 0) {
            printf("Login successful. Redirecting to home page...\n");
            return;
        }
    }
    printf("Invalid credentials. Redirecting back to login page...\n");
}

int main() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter username: ");
    scanf("%49s", inputUsername);
    printf("Enter password: ");
    scanf("%49s", inputPassword);

    login(inputUsername, inputPassword);

    return 0;
}