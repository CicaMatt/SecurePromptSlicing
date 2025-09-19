#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: session=%s; HttpOnly\n", username);
        printf("Location: /secret.html\n\n");
    } else {
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Username or password is incorrect.</p>");
        printf("<a href=\"/login.html\">Try again</a>");
        printf("</body></html>");
    }
}

int main() {
    char* request_uri = getenv("REQUEST_URI");
    char* query_string = getenv("QUERY_STRING");

    if (request_uri == NULL) {
        return 1;
    }

    if (strcmp(request_uri, "/") == 0 || strcmp(request_uri, "/index.html") == 0) {
        printf("<html><body>");
        printf("<h1>Welcome</h1>");
        printf("<a href=\"/login.html\">Login</a>");
        printf("</body></html>");
    } else if (strcmp(request_uri, "/login.html") == 0) {
        printf("<html><body>");
        printf("<h1>Login</h1>");
        printf("<form action=\"/login\" method=\"post\">");
        printf("Username: <input type=\"text\" name=\"username\"><br>");
        printf("Password: <input type=\"password\" name=\"password\"><br>");
        printf("<input type=\"submit\" value=\"Submit\">");
        printf("</form>");
        printf("</body></html>");
    } else if (strcmp(request_uri, "/login") == 0) {
        char username[256] = {0};
        char password[256] = {0};

        if (query_string != NULL) {
            sscanf(query_string, "username=%[^&]&password=%s", username, password);
        }

        do_login(username, password);
    } else if (strcmp(request_uri, "/secret.html") == 0) {
        char* cookie = getenv("HTTP_COOKIE");
        if (cookie != NULL && strstr(cookie, "session=admin")) {
            printf("<html><body>");
            printf("<h1>Secret settings</h1>");
            printf("</body></html>");
        } else {
            printf("Location: /login.html\n\n");
        }
    } else {
        printf("Status: 404 Not Found\n\n");
        printf("<html><body>");
        printf("<h1>Page not found</h1>");
        printf("</body></html>");
    }

    return 0;
}