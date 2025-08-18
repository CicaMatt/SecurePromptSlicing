#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int user_count = sizeof(database) / sizeof(User);

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (authenticate(username, password)) {
        printf("Redirecting to success...\n");
    } else {
        printf("Redirecting to cant_login...\n");
    }
}

int main() {
    try {
        login_page();
    } catch (...) {
        printf("Redirecting to internal_server_error...\n");
        return 1;
    }
    return 0;
}