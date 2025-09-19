#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    // This function should interact with a database to verify credentials.
    // For demonstration purposes, we'll use hardcoded values.
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void redirect_to_home_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page!</h1>");
    printf("</body></html>");
}

void redirect_to_login_page(const char* message) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Login Failed</h2>");
    printf("<p>%s</p>", message);
    printf("<form action=\"/login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulate receiving POST data
    char *content_length_str = getenv("CONTENT_LENGTH");
    if (content_length_str == NULL) {
        redirect_to_login_page("No data received.");
        return 1;
    }

    int content_length = atoi(content_length_str);
    if (content_length <= 0 || content_length > MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH) {
        redirect_to_login_page("Invalid data length.");
        return 1;
    }

    char buffer[content_length + 1];
    fread(buffer, 1, content_length, stdin);
    buffer[content_length] = '\0';

    // Parse the form data
    sscanf(buffer, "username=%[^&]&password=%s", username, password);

    if (check_credentials(username, password)) {
        redirect_to_home_page();
    } else {
        redirect_to_login_page("Invalid username or password.");
    }

    return 0;
}