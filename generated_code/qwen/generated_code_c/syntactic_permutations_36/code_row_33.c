#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int user_count = sizeof(users) / sizeof(User);

int check_credentials(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return strcmp(users[i].password, password) == 0;
        }
    }
    return 0;
}

void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (check_credentials(username, password)) {
        printf("Redirecting to Home Page...\n");
    } else {
        printf("Invalid Username or Password.\n");
    }
}

int main() {
    printf("Welcome to the Login Page\n");
    login();
    return 0;
}