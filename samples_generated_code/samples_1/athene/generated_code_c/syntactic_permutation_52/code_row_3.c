#include <stdio.h>
#include <string.h>

char *session_username = NULL;

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        session_username = strdup(username);
        printf("Location: /secret\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Redirecting...</title></head><body>");
        printf("<p>Logging in...</p>");
        printf("</body></html>\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Login Failed</title></head><body>");
        printf("<p>Invalid username or password.</p>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>\n");
    }
}

void index() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Index Page</title></head><body>");
    printf("<p>Welcome! Please <a href=\"/login\">log in</a>.</p>");
    printf("</body></html>\n");
}

void secret() {
    if (session_username == NULL) {
        printf("Location: /login\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Redirecting...</title></head><body>");
        printf("<p>You must be logged in to view this page.</p>");
        printf("</body></html>\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Secret Page</title></head><body>");
        printf("<p>Secret settings</p>");
        printf("</body></html>\n");
    }
}

int main() {
    const char *path = getenv("PATH_INFO");
    if (strcmp(path, "/login") == 0) {
        const char *method = getenv("REQUEST_METHOD");
        if (strcmp(method, "POST") == 0) {
            do_login(getenv("HTTP_USERNAME"), getenv("HTTP_PASSWORD"));
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><head><title>Login Page</title></head><body>");
            printf("<form method=\"post\" action=\"/login\">");
            printf("<label for=\"username\">Username:</label>");
            printf("<input type=\"text\" id=\"username\" name=\"username\"><br>");
            printf("<label for=\"password\">Password:</label>");
            printf("<input type=\"password\" id=\"password\" name=\"password\"><br>");
            printf("<button type=\"submit\">Login</button>");
            printf("</form></body></html>\n");
        }
    } else if (strcmp(path, "/") == 0) {
        index();
    } else if (strcmp(path, "/secret") == 0) {
        secret();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>404 Not Found</title></head><body>");
        printf("<p>The requested resource was not found.</p>");
        printf("</body></html>\n");
    }
    return 0;
}