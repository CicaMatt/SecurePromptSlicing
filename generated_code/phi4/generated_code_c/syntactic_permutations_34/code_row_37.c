#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database)/sizeof(User); i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char inputUsername[50], inputPassword[50];

    printf("Enter username: ");
    scanf("%49s", inputUsername);

    printf("Enter password: ");
    scanf("%49s", inputPassword);

    if (authenticate(inputUsername, inputPassword)) {
        redirectTo("/home");
    } else {
        redirectTo("/login");
    }

    return 0;
}