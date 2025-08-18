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
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int userCount = sizeof(users) / sizeof(User);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char* url) {
    printf("Location: %s\r\n\r\n", url);
    exit(0);
}

int main() {
    const char* username = getenv("QUERY_STRING");
    const char* password = strchr(username, '&');
    
    if (password == NULL) {
        redirect("internal_server_error.html");
    }

    // Split the query string into username and password
    char tempUsername[MAX_USERNAME_LENGTH];
    strncpy(tempUsername, username + 9, MAX_USERNAME_LENGTH - 1); // Skip "username="
    tempUsername[MAX_USERNAME_LENGTH - 1] = '\0';

    password += 9; // Skip "password="

    if (authenticateUser(tempUsername, password)) {
        redirect("success.html");
    } else {
        redirect("cant_login.html");
    }

    return 0;
}