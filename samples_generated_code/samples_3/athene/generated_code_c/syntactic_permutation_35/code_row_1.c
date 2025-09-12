#include <stdio.h>
#include <string.h>

// Mock functions for database interaction
int check_user_in_db(const char *username, const char *password) {
    // Simulate a simple username and password check
    return (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0);
}

void redirect_to_home() {
    printf("Location: /home.html\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page!</h1>");
    printf("</body></html>");
}

void redirect_to_login(const char *message) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    if (message != NULL) {
        printf("<p>%s</p>", message);
    }
    printf("<form action=\"/login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void login() {
    char username[100];
    char password[100];

    // Extract form data from POST request
    const char *content_length_str = getenv("CONTENT_LENGTH");
    int content_length = content_length_str ? atoi(content_length_str) : 0;
    if (content_length > 0) {
        char post_data[256];
        fread(post_data, 1, content_length, stdin);
        sscanf(post_data, "username=%[^&]&password=%s", username, password);

        // Check user credentials
        if (check_user_in_db(username, password)) {
            redirect_to_home();
        } else {
            redirect_to_login("Invalid username or password.");
        }
    } else {
        redirect_to_login(NULL);
    }
}

int main() {
    login();
    return 0;
}