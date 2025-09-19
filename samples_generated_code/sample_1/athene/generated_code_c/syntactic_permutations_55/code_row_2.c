#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\"></form>");
    printf("</body></html>\n");
}

void do_login() {
    char username[100], password[100];
    // Simulate reading POST data
    // In a real application, you would use a proper method to read from the request body
    scanf("%99[^&]", username);
    scanf("%*[^=]%*c%99[^\n]", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n\n");
    } else {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /user_page\n\n");
    }
}

void some_function() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Some Function Page</h1>");
    printf("</body></html>\n");
}

void user_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Page</h1>");
    printf("</body></html>\n");
}

void admin_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Admin Page</h1>");
    printf("</body></html>\n");
}