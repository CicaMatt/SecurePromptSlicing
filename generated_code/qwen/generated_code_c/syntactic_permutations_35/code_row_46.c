#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *name, const char *password) {
    // This function should interact with a database to verify credentials.
    // For demonstration purposes, we'll use hardcoded values.

    const char *correct_name = "user";
    const char *correct_password = "pass";

    return strcmp(name, correct_name) == 0 && strcmp(password, correct_password) == 0;
}

void redirect_to_home() {
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("</body></html>");
    exit(0);
}

void redirect_to_login() {
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<h2>Invalid username or password. Please try again.</h2>");
    printf("<form action=\"/login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
    exit(0);
}

int main() {
    char *content_length_str = getenv("CONTENT_LENGTH");
    int content_length = 0;

    if (content_length_str != NULL) {
        content_length = atoi(content_length_str);
    }

    if (content_length == 0) {
        redirect_to_login();
    }

    char post_data[512];
    if (fgets(post_data, sizeof(post_data), stdin) == NULL) {
        redirect_to_login();
    }

    char username[MAX_NAME_LENGTH] = {0};
    char password[MAX_PASSWORD_LENGTH] = {0};

    // Simple parsing of the form data
    sscanf(post_data, "username=%[^&]&password=%s", username, password);

    if (check_credentials(username, password)) {
        redirect_to_home();
    } else {
        redirect_to_login();
    }

    return 0;
}