#include <stdio.h>
#include <string.h>

// Simulated database entries
#define MAX_USERS 2
const char *db_users[MAX_USERS][2] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

void redirectTo(const char *page) {
    printf("Redirecting to: %s\n", page);
}

int checkCredentials(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(db_users[i][0], username) == 0 && strcmp(db_users[i][1], password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    int result = checkCredentials(username, password);
    
    if (result == 1) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }
}

int main() {
    char username[50], password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    login(username, password);

    return 0;
}