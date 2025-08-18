#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        setenv("SESSION_USERNAME", username, 1);
        printf("Location: /secret\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Redirecting...</title></head><body>");
        printf("<h1>Redirecting to secret page...</h1>");
        printf("</body></html>\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Login Failed</title></head><body>");
        printf("<h1>Login failed. Please try again.</h1>");
        printf("<a href=\"/login\">Try Again</a>");
        printf("</body></html>\n");
    }
}

void login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Login</title></head><body>");
    printf("<h1>Login</h1>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br>");
    printf("<label for=\"password\">Password:</label>");
    printf("<input type=\"password\" id=\"password\" name=\"password\"><br>");
    printf("<button type=\"submit\">Login</button>");
    printf("</form></body></html>\n");
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Index</title></head><body>");
    printf("<h1>Welcome!</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>\n");
}

void secret_page() {
    const char *username = getenv("SESSION_USERNAME");
    if (username == NULL || strlen(username) == 0) {
        printf("Location: /index\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Access Denied</title></head><body>");
        printf("<h1>You must be logged in to access this page.</h1>");
        printf("<a href=\"/login\">Login</a>");
        printf("</body></html>\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Secret Settings</title></head><body>");
        printf("<h1>Secret settings</h1>");
        printf("<p>Welcome, %s!</p>", username);
        printf("</body></html>\n");
    }
}

int main() {
    const char *path_info = getenv("PATH_INFO");
    if (strcmp(path_info, "/login") == 0) {
        login_page();
    } else if (strcmp(path_info, "/do_login") == 0) {
        const char *username = getenv("HTTP_X_USERNAME");
        const char *password = getenv("HTTP_X_PASSWORD");
        do_login(username, password);
    } else if (strcmp(path_info, "/index") == 0 || path_info == NULL) {
        index_page();
    } else if (strcmp(path_info, "/secret") == 0) {
        secret_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>404 Not Found</title></head><body>");
        printf("<h1>Page not found.</h1>");
        printf("</body></html>\n");
    }
    return 0;
}