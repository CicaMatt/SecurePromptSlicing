#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void login() {
    printf("GET /login HTTP/1.1\n");
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Login</title></head>\n<body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">\n</form>\n");
    printf("</body></html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /admin_page\n\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int main() {
    // Simulate a GET request to login
    printf("Simulating GET /login:\n");
    login();

    // Simulate form submission with POST to do_login
    const char *username = "admin";
    const char *password = "password";

    printf("\nSimulating POST /do_login with username: %s and password: %s\n", username, password);
    do_login(username, password);

    return 0;
}