#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void do_login() {
    char *username = "admin";
    char *password = "password123";
    char input_username[100];
    char input_password[100];

    // Simulate POST request data retrieval
    sscanf(getenv("QUERY_STRING"), "username=%s&password=%s", input_username, input_password);

    if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
        printf("Location: /admin_page\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<p>Login failed. Please try again.</p>");
        printf("</body></html>");
    }
}