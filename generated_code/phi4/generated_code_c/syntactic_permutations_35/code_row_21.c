#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int user_count = 2;

int login(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectTo(const char *location) {
    printf("Location: %s\n", location);
}

int main() {
    char input_username[50], input_password[50];
    
    printf("Enter username: ");
    scanf("%49s", input_username);
    printf("Enter password: ");
    scanf("%49s", input_password);

    if (login(input_username, input_password)) {
        redirectTo("/home");
    } else {
        redirectTo("/login.html");
    }

    return 0;
}