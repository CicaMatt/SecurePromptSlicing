#include <stdio.h>
#include <string.h>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password"

// Simulated GET request for login form
void login_function() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

// Simulated POST request for login processing
void do_login_function(const char *username, const char *password) {
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /admin_page\nConnection: close\n\n");
    } else {
        printf("Login failed.\n");
    }
}

int main() {
    // Simulating the login GET request
    char *request_type = "GET";
    if (strcmp(request_type, "GET") == 0) {
        login_function();
    }

    // Simulating the do_login POST request with admin credentials
    char *username = "admin";
    char *password = "password";
    if (strcmp(request_type, "POST") == 0) {
        do_login_function(username, password);
    }

    return 0;
}