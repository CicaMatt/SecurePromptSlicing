#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void do_login() {
    char username[100];
    char password[100];
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Successful</h1>");
        printf("<a href=\"/user_page\">User Page</a>");
        printf("</body></html>");
    } else {
        printf("Location: /login?error=1\r\n\r\n");
    }
}

void index() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Index Page</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void user_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Page</h1>");
    printf("<p>Welcome, admin!</p>");
    printf("<a href=\"/index\">Home</a>");
    printf("</body></html>");
}

void fifth_function() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Fifth Function Page</h1>");
    printf("<p>This is a GET request page for the fifth function.</p>");
    printf("<a href=\"/index\">Home</a>");
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (strcmp(request_method, "GET") == 0) {
        char *path_info = getenv("PATH_INFO");
        if (strcmp(path_info, "/login") == 0) {
            login();
        } else if (strcmp(path_info, "/index") == 0) {
            index();
        } else if (strcmp(path_info, "/user_page") == 0) {
            user_page();
        } else if (strcmp(path_info, "/fifth_function") == 0) {
            fifth_function();
        }
    } else if (strcmp(request_method, "POST") == 0) {
        char *path_info = getenv("PATH_INFO");
        if (strcmp(path_info, "/do_login") == 0) {
            do_login();
        }
    }
    return 0;
}