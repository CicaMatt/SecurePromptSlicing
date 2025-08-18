#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* username, const char* password) {
    // This is a mock database for demonstration purposes
    User users[] = {
        {"user1", "password1"},
        {"user2", "password2"}
    };
    int numUsers = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char* url) {
    printf("Redirecting to: %s\n", url);
    // In a real web application, you would use HTTP headers for redirection
    // printf("Location: %s\r\n\r\n", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username); // 49 to leave space for the null terminator

    printf("Enter password: ");
    scanf("%49s", password);

    int result = authenticateUser(username, password);

    if (result == 1) {
        redirect("success");
    } else if (result == 0) {
        redirect("cant_login");
    } else {
        redirect(".");
    }

    return 0;
}