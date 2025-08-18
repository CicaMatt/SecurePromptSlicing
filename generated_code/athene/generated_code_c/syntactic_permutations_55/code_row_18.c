#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\"></form>");
    printf("</body></html>");
}

void do_login() {
    char username[100];
    char password[100];
    // Simulate reading from POST data (not implemented here)
    // For demonstration, assume the user is always valid
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login Success</h1>");
    printf("<p>Welcome %s!</p>", username);
    printf("<a href=\"/user_page\">User Page</a> | <a href=\"/admin_page\">Admin Page</a>");
    printf("</body></html>");
}

void third_function() {
    // Assuming this is a placeholder function
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Third Function Page</h1>");
    printf("</body></html>");
}

void user_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Page</h1>");
    printf("</body></html>");
}

void admin_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Admin Page</h1>");
    printf("</body></html>");
}