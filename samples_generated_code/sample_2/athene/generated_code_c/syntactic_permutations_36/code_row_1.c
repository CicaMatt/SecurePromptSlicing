#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"admin", "password123"},
    {"user1", "pass456"}
};

#define DATABASE_SIZE (sizeof(database) / sizeof(User))

void login(const char *username, const char *password) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(username, database[i].username) == 0) {
            if (strcmp(password, database[i].password) == 0) {
                printf("Login successful. Redirecting to home page.\n");
                return;
            } else {
                printf("Incorrect password.\n");
                return;
            }
        }
    }
    printf("User not found.\n");
}

int main() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);
    return 0;
}