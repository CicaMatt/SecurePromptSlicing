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
    printf("</form></body></html>\n");
}

void do_login() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login Result</h1>");
    char *username = getenv("HTTP_USERNAME");
    char *password = getenv("HTTP_PASSWORD");
    if (username && password && strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        printf("<p>Login successful!</p>");
        printf("<a href=\"/user_page\">User Page</a><br>");
        printf("<a href=\"/admin_page\">Admin Page</a>");
    } else {
        printf("<p>Login failed. <a href=\"/login\">Try again</a></p>");
    }
    printf("</body></html>\n");
}

void index() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>\n");
}

void user_page() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Page</h1>");
    printf("<p>Welcome, User!</p>");
    printf("<a href=\"/index\">Home</a>");
    printf("</body></html>\n");
}

void admin_page() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Admin Page</h1>");
    printf("<p>Welcome, Admin!</p>");
    printf("<a href=\"/index\">Home</a>");
    printf("</body></html>\n");
}