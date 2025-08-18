#include <stdio.h>
#include <stdlib.h>

void login() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void do_login() {
    char *username = getenv("HTTP_USERNAME");
    char *password = getenv("HTTP_PASSWORD");
    if (username && password) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            printf("HTTP/1.1 302 Found\nLocation: /admin_page\n\n");
        } else {
            printf("HTTP/1.1 302 Found\nLocation: /user_page\n\n");
        }
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/html\n\n");
        printf("<html><body><h1>Invalid credentials</h1></body></html>");
    }
}

void index() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void user_page() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome User!</h1>");
    printf("<a href=\"/index\">Home</a>");
    printf("</body></html>");
}

void admin_page() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome Admin!</h1>");
    printf("<a href=\"/index\">Home</a>");
    printf("</body></html>");
}