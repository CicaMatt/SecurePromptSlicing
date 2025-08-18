#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    // This function should interact with a database to verify credentials.
    // For demonstration purposes, we'll use hardcoded values.
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Credentials are correct
    }
    return 0; // Credentials are incorrect
}

void handle_login(const char* username, const char* password) {
    if (check_credentials(username, password)) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome to the Home Page</h1>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Invalid username or password. <a href=\"login.html\">Try again</a>.</p>");
        printf("</body></html>");
    }
}

int main() {
    char* method = getenv("REQUEST_METHOD");
    if (method == NULL || strcmp(method, "POST") != 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Invalid request method</h1>");
        printf("</body></html>");
        return 1;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Read the form data from POST request
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    if (content_length > 0) {
        char buffer[content_length + 1];
        fread(buffer, sizeof(char), content_length, stdin);
        buffer[content_length] = '\0';

        // Parse the input to extract username and password
        sscanf(buffer, "username=%[^&]&password=%s", username, password);

        handle_login(username, password);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Invalid form data</h1>");
        printf("</body></html>");
    }

    return 0;
}