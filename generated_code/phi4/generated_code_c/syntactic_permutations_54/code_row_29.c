#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Login</title></head>\n<body>\n");
    printf("<form action=\"/do_login\" method=\"POST\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n</body></html>\n");
}

void do_login() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    // Simulate reading POST data
    printf("Content-Type: text/html\n\n");
    if (fgets(username, MAX_USERNAME_LEN, stdin) && fgets(password, MAX_PASSWORD_LEN, stdin)) {
        // Remove newline characters
        username[strcspn(username, "\n")] = '\0';
        password[strcspn(password, "\n")] = '\0';

        // Hardcoded credentials for demonstration purposes
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            printf("<html>\n<head><title>Admin Page</title></head>\n<body>\n");
            printf("<h1>Welcome to the admin page!</h1>\n");
            printf("</body></html>\n");
        } else {
            printf("<html>\n<head><title>Login Failed</title></head>\n<body>\n");
            printf("<h1>Invalid username or password.</h1>\n");
            printf("<a href=\"/\">Try again</a>\n");
            printf("</body></html>\n");
        }
    } else {
        printf("<html>\n<head><title>Error</title></head>\n<body>\n");
        printf("<h1>There was an error processing your login.</h1>\n");
        printf("</body></html>\n");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        do_login();
    }

    return 0;
}