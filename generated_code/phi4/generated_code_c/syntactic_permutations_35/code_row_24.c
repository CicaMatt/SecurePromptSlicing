#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int find_user(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char input_username[50], input_password[50];

    printf("Enter username: ");
    scanf("%49s", input_username);

    printf("Enter password: ");
    scanf("%49s", input_password);

    if (find_user(input_username, input_password)) {
        redirect("home.html");
    } else {
        redirect("login.html");
    }

    return 0;
}