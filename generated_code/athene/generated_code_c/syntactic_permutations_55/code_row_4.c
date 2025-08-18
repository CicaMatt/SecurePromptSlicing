#include <stdio.h>
#include <stdlib.h>

void login() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>\n");
}

void do_login() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Login Result</h1>");
    printf("<p>Processing login...</p>");
    // Simulate processing
    printf("</body></html>\n");
}

void index() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Index Page</h1>");
    printf("<p>Welcome to the homepage!</p>");
    printf("</body></html>\n");
}

void user_page() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Page</h1>");
    printf("<p>Welcome, user!</p>");
    printf("</body></html>\n");
}

void admin_page() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Admin Page</h1>");
    printf("<p>Welcome, admin!</p>");
    printf("</body></html>\n");
}