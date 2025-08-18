#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* username, const char* password) {
    // This is a mock database for demonstration purposes
    User users[] = {
        {"user1", "pass1"},
        {"admin", "admin123"}
    };
    int userCount = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char* url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
    exit(0);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulating input for demonstration purposes
    strcpy(username, "admin");
    strcpy(password, "admin123");

    if (fgets(username, sizeof(username), stdin) != NULL && fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline characters from username and password
        username[strcspn(username, "\n")] = 0;
        password[strcspn(password, "\n")] = 0;

        int authResult = authenticateUser(username, password);
        if (authResult == 1) {
            redirect("success.html");
        } else if (authResult == 0) {
            redirect("cant_login.html");
        }
    }
    redirect("internal_server_error.html");

    return 0;
}