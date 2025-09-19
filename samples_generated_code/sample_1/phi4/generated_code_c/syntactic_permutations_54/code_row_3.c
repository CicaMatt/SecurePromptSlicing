#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate HTTP GET request handling for login
void login_function() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Login</title></head>\n<body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">\n</form>\n");
    printf("</body></html>\n");
}

// Mock function to simulate HTTP POST request handling for login
void do_login_function(const char *username, const char *password) {
    // In a real scenario, use secure authentication methods and database checks

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Location: /admin_page\n");
        printf("Status: 302 Found\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html>\n<head><title>Login Failed</title></head>\n<body>\n");
        printf("<p>Invalid username or password.</p>\n");
        printf("<a href=\"/\">Try again</a>\n");
        printf("</body></html>\n");
    }
}

int main() {
    // Simulating a GET request for login
    login_function();

    // For demonstration purposes, simulate a POST request with hardcoded values
    const char *username = "admin";
    const char *password = "admin123";

    printf("\n---\n\n"); // Separator to mimic HTTP requests

    // Simulating a POST request for do_login
    do_login_function(username, password);

    return 0;
}