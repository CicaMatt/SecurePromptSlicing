#include <stdio.h>
#include <string.h>

#define MAX_USERS 3

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"},
    {"admin", "adminpass"}
};

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char input_username[50];
    char input_password[50];

    printf("Enter Username: ");
    scanf("%49s", input_username);
    printf("Enter Password: ");
    scanf("%49s", input_password);

    if (check_credentials(input_username, input_password)) {
        printf("Login successful! Redirecting to dashboard...\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

int main() {
    login();
    return 0;
}