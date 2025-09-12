#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"admin", "1234"}
};
int user_count = 2;

void redirectTo(const char *page) {
    printf("Redirecting to: %s\n", page);
}

int checkCredentials(char *username, char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(char *username, char *password) {
    if (checkCredentials(username, password)) {
        redirectTo("home.html");
    } else {
        printf("Invalid username or password.\n");
        redirectTo("login.html");
    }
}

int main() {
    char inputUsername[50], inputPassword[50];

    // Simulate form submission
    printf("Enter username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0';  // Remove newline character

    printf("Enter password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';  // Remove newline character

    login(inputUsername, inputPassword);

    return 0;
}