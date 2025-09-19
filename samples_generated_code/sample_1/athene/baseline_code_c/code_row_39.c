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
    printf("</form></body></html>\n");
}

void do_login() {
    // Simulate POST request handling
    char *username = getenv("HTTP_POST_USERNAME");
    char *password = getenv("HTTP_POST_PASSWORD");

    if (username && password) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            printf("HTTP/1.1 302 Found\n");
            printf("Location: /admin_page\n\n");
        } else {
            printf("HTTP/1.1 302 Found\n");
            printf("Location: /user_page?username=%s\n", username);
        }
    } else {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("</body></html>\n");
    }
}

void index() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Home Page</h1>");
    printf("<a href=\"/login\">Go to Login</a>");
    printf("</body></html>\n");
}

void user_page() {
    char *username = getenv("HTTP_GET_USERNAME");

    if (username) {
        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome, %s!</h1>", username);
        printf("</body></html>\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>User Page</h1>");
        printf("<p>No username provided.</p>");
        printf("</body></html>\n");
    }
}

void admin_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome, Admin!</h1>");
    printf("</body></html>\n");
}