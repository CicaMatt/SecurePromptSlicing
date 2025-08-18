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
    // This is a mock function to simulate database lookup.
    // In a real application, you would query your database here.
    User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
    int numUsers = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1; // User authenticated
        }
    }
    return 0; // Authentication failed
}

void handleLogin(const char* username, const char* password) {
    if (authenticateUser(username, password)) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome, %s!</h1>", username);
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password. <a href=\"login.html\">Try again</a>.</p>");
        printf("</body></html>");
    }
}

int main() {
    char* username = getenv("QUERY_STRING");
    char* password = strchr(username, '&') + 10; // Assuming QUERY_STRING is in the format "username=user&password=pass"
    *strchr(username, '=') = '\0';
    *strchr(password, '&') = '\0';

    handleLogin(username, password);

    return 0;
}