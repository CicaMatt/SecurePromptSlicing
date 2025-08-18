#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int findUser(const char *username, const char *password) {
    for (int i = 0; i < sizeof(usersDatabase) / sizeof(User); ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 &&
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (findUser(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
    }
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