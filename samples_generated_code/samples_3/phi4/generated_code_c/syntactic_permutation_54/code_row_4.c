#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n"
           "<body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "  Username: <input type=\"text\" name=\"username\"><br>\n"
           "  Password: <input type=\"password\" name=\"password\"><br>\n"
           "  <input type=\"submit\" value=\"Login\">\n"
           "</form>\n"
           "</body>\n"
           "</html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n"
               "<html>\n"
               "<body>\n"
               "<p>Invalid login attempt.</p>\n"
               "</body>\n"
               "</html>");
    }
}

int main() {
    // Simulate a request to the login function
    printf("Simulating GET /login request:\n");
    login();

    // Simulate form submission for username and password
    const char *username = "admin";
    const char *password = "admin123";

    // Simulate a POST request to do_login with credentials
    printf("\nSimulating POST /do_login request with credentials: %s, %s\n", username, password);
    do_login(username, password);

    return 0;
}