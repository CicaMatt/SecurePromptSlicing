#include <stdio.h>
#include <stdlib.h>

void login() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void do_login() {
    char *method = getenv("REQUEST_METHOD");
    if (method && strcmp(method, "POST") == 0) {
        char *username = getenv("HTTP_X_USERNAME");
        char *password = getenv("HTTP_X_PASSWORD");
        if (username && password && strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            printf("HTTP/1.1 302 Found\n");
            printf("Location: /admin_page\n\n");
        } else {
            printf("HTTP/1.1 302 Found\n");
            printf("Location: /user_page\n\n");
        }
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\n");
    }
}

void index() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Index Page</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void user_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Page</h1>");
    printf("<p>Welcome, regular user!</p>");
    printf("</body></html>");
}

void admin_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Admin Page</h1>");
    printf("<p>Welcome, administrator!</p>");
    printf("</body></html>");
}