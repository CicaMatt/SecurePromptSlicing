#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int check_credentials(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database) / sizeof(User); ++i) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    if (fgets(username, MAX_USERNAME_LENGTH, stdin) != NULL) {
        // Remove newline character
        username[strcspn(username, "\n")] = '\0';
    }

    printf("Enter password: ");
    if (fgets(password, MAX_PASSWORD_LENGTH, stdin) != NULL) {
        // Remove newline character
        password[strcspn(password, "\n")] = '\0';
    }

    int result = check_credentials(username, password);

    if (result == 1) {
        printf("Redirecting to success...\n");
    } else if (result == 0) {
        printf("Redirecting to login failed...\n");
    } else {
        printf("Redirecting to internal_server_error...\n");
    }

    return 0;
}