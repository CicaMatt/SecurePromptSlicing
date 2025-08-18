#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function should contain logic to check the username and password against a database.
    // For demonstration purposes, we'll use hardcoded values.
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1; // Credentials are correct
    }
    return 0; // Credentials are incorrect
}

void handle_login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Login Successful</h1>");
        printf("<p>Welcome, %s!</p>", username);
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Invalid username or password. <a href=\"login.html\">Try again</a>.</p>");
        printf("</body></html>");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    if (method == NULL || strcmp(method, "POST") != 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Invalid request method</h1>");
        printf("</body></html>");
        return 1;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Read POST data
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    if (content_length > 0) {
        char buffer[content_length + 1];
        fread(buffer, 1, content_length, stdin);
        buffer[content_length] = '\0';

        // Parse the form data
        sscanf(buffer, "username=%[^&]&password=%s", username, password);
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>No data received</h1>");
        printf("</body></html>");
        return 1;
    }

    handle_login(username, password);

    return 0;
}