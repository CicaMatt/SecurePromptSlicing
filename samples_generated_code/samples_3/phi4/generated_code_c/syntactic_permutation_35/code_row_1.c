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

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(User); ++i) {
        if (strcmp(database[i].username, username) == 0 &&
            strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    login(username, password);

    return 0;
}