#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate_user(const char* username, const char* password) {
    // This function would normally interact with a database
    // For demonstration, we'll use hardcoded credentials
    User users[] = {
        {"user1", "pass1"},
        {"admin", "admin123"}
    };
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login(const char* username, const char* password) {
    if (authenticate_user(username, password)) {
        printf("Location: home.html\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Invalid username or password. <a href=\"login.html\">Try again</a>.</p>");
        printf("</body></html>");
    }
}

int main() {
    char* method = getenv("REQUEST_METHOD");
    if (method == NULL || strcmp(method, "POST") != 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Invalid request method</h1>");
        printf("</body></html>");
        return 1;
    }

    char buffer[1024];
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    if (content_length <= 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>No data received</h1>");
        printf("</body></html>");
        return 1;
    }

    int total_read = 0;
    while (total_read < content_length) {
        int bytes_read = fread(buffer + total_read, 1, content_length - total_read, stdin);
        if (bytes_read <= 0) break;
        total_read += bytes_read;
    }
    buffer[content_length] = '\0';

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    sscanf(buffer, "username=%[^&]&password=%s", username, password);

    handle_login(username, password);

    return 0;
}