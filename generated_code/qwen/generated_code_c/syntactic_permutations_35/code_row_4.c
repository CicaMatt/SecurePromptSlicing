#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    // This function should interact with a database.
    // For demonstration purposes, we'll use hardcoded values.
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Credentials are correct
    }
    return 0; // Credentials are incorrect
}

void redirect_to_home() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("</body></html>");
}

void redirect_to_login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login Failed</h1>");
    printf("<form action=\"login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    char *data;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    data = getenv("CONTENT_LENGTH");

    if (data != NULL) {
        int len = atoi(data);
        if (len > 0 && len < MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2) { // +2 for '&' and '\0'
            fread(username, 1, len, stdin);
            username[strcspn(username, "&")] = '\0'; // Null-terminate the username
            strcpy(password, strchr(username, '=') + 1); // Extract password
            memmove(username, strchr(username, '=') + 1, strlen(strchr(username, '=') + 1) - strlen(password));
            
            if (check_credentials(username, password)) {
                redirect_to_home();
            } else {
                redirect_to_login();
            }
        } else {
            redirect_to_login();
        }
    } else {
        redirect_to_login();
    }

    return 0;
}