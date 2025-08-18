#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function should check the credentials against a database.
    // For demonstration purposes, we will use hardcoded values.
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void redirect_to_home() {
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><head><title>Home</title></head>");
    printf("<body><h1>Welcome to the Home Page!</h1></body>");
    printf("</html>");
}

void redirect_to_login() {
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><head><title>Login Failed</title></head>");
    printf("<body><h1>Login failed. Please try again.</h1>");
    printf("<a href=\"login.html\">Go back to login page</a>");
    printf("</body>");
    printf("</html>");
}

int main() {
    char *content_length_str = getenv("CONTENT_LENGTH");
    int content_length = 0;
    if (content_length_str != NULL) {
        content_length = atoi(content_length_str);
    }

    char buffer[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 1];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        char username[MAX_USERNAME_LENGTH + 1] = "";
        char password[MAX_PASSWORD_LENGTH + 1] = "";

        sscanf(buffer, "username=%[^&]&password=%s", username, password);

        if (check_credentials(username, password)) {
            redirect_to_home();
        } else {
            redirect_to_login();
        }
    }

    return 0;
}