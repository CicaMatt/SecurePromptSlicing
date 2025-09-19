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
    {"user3", "password3"}
};

void redirectTo(const char* page) {
    printf("Redirecting to %s\n", page);
}

int checkCredentials(const char* username, const char* password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter Username: ");
    if (scanf("%49s", inputUsername) != 1) {
        redirectTo("internal_server_error");
        return;
    }

    printf("Enter Password: ");
    if (scanf("%49s", inputPassword) != 1) {
        redirectTo("internal_server_error");
        return;
    }

    if (checkCredentials(inputUsername, inputPassword)) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }
}

int main() {
    loginPage();
    return 0;
}