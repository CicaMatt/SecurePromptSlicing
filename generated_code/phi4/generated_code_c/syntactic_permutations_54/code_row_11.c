#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n"
           "<head><title>Login</title></head>\n"
           "<body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "  Username: <input type=\"text\" name=\"username\"><br>\n"
           "  Password: <input type=\"password\" name=\"password\"><br>\n"
           "  <input type=\"submit\" value=\"Login\">\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

void do_login() {
    char username[50], password[50];

    // Simulating receiving POST data
    printf("Content-Type: text/html\n\n");

    if (fgets(username, sizeof(username), stdin) && fgets(password, sizeof(password), stdin)) {
        // Remove newline character from fgets input
        size_t len1 = strlen(username);
        if (len1 > 0 && username[len1 - 1] == '\n') username[--len1] = '\0';

        size_t len2 = strlen(password);
        if (len2 > 0 && password[len2 - 1] == '\n') password[--len2] = '\0';
        
        // Check if the user is admin
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            printf("<html>\n"
                   "<head><title>Admin Page</title></head>\n"
                   "<body>\n"
                   "<h1>Welcome to the Admin Page!</h1>\n"
                   "</body>\n"
                   "</html>\n");
        } else {
            printf("<html>\n"
                   "<head><title>Login Failed</title></head>\n"
                   "<body>\n"
                   "<p>Invalid username or password.</p>\n"
                   "<form action=\"/login\" method=\"get\">\n"
                   "  <input type=\"submit\" value=\"Try Again\">\n"
                   "</form>\n"
                   "</body>\n"
                   "</html>\n");
        }
    } else {
        printf("<html>\n"
               "<head><title>Error</title></head>\n"
               "<body>\n"
               "<p>Error processing login.</p>\n"
               "</body>\n"
               "</html>\n");
    }
}

int main() {
    char method[10];

    // Simulating a web server environment
    fgets(method, sizeof(method), stdin);

    if (strcmp(method, "GET\n") == 0) {
        login();
    } else if (strcmp(method, "POST\n") == 0) {
        do_login();
    }

    return 0;
}