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
    User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
    int numUsers = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handleLogin(const char* username, const char* password) {
    if (authenticateUser(username, password)) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Redirecting to home page...</body></html>");
        printf("<meta http-equiv=\"refresh\" content=\"0;url=home.html\">");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Invalid username or password. Redirecting back to login page...</body></html>");
        printf("<meta http-equiv=\"refresh\" content=\"0;url=login.html\">");
    }
}

int main() {
    char* method = getenv("REQUEST_METHOD");

    if (method && strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            char buffer[1024];
            int len = fread(buffer, 1, sizeof(buffer)-1, stdin);
            buffer[len] = '\0';

            char username[MAX_USERNAME_LENGTH];
            char password[MAX_PASSWORD_LENGTH];
            sscanf(buffer, "username=%[^&]&password=%s", username, password);

            handleLogin(username, password);
        }
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Invalid request method.</body></html>");
    }

    return 0;
}