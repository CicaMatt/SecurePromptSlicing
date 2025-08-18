#include <stdio.h>
#include <string.h>

// Mock database for simplicity
typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "pass1"},
    {"admin", "root"}
};

int user_count = 2;

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            printf("Login successful! Redirecting to dashboard...\n");
            return;
        }
    }
    printf("Invalid credentials. Redirecting back to login page.\n");
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