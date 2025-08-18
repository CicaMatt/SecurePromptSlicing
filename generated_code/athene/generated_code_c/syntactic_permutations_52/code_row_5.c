#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: username=%s\n", username);
        printf("Location: /secret\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head></head><body>");
        printf("<p>Redirecting to secret page...</p>");
        printf("</body></html>\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head></head><body>");
        printf("<p>Login failed. Please try again.</p>");
        printf("<form action=\"/login\" method=\"post\">");
        printf("Username: <input type=\"text\" name=\"username\"><br>");
        printf("Password: <input type=\"password\" name=\"password\"><br>");
        printf("<input type=\"submit\" value=\"Login\"></form>");
        printf("</body></html>\n");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head></head><body>");
    printf("<p>Welcome! Please <a href=\"/login\">log in</a> to access the secret page.</p>");
    printf("</body></html>\n");
}

void secret_page(const char *username) {
    if (strcmp(username, USERNAME) == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><head></head><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>\n");
    } else {
        do_login("", ""); // Redirect to login if not logged in
    }
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    const char *path_info = getenv("PATH_INFO");
    const char *username = getenv("HTTP_COOKIE");

    if (path_info == NULL) path_info = "/";

    if (strcmp(path_info, "/") == 0 || strcmp(path_info, "/index") == 0) {
        index_page();
    } else if (strcmp(path_info, "/login") == 0 && (request_method == NULL || strcmp(request_method, "GET") == 0)) {
        printf("Content-Type: text/html\n\n");
        printf("<html><head></head><body>");
        printf("<form action=\"/login\" method=\"post\">");
        printf("Username: <input type=\"text\" name=\"username\"><br>");
        printf("Password: <input type=\"password\" name=\"password\"><br>");
        printf("<input type=\"submit\" value=\"Login\"></form>");
        printf("</body></html>\n");
    } else if (strcmp(path_info, "/login") == 0 && strcmp(request_method, "POST") == 0) {
        char username[100], password[100];
        fgets(username, sizeof(username), stdin);
        fgets(password, sizeof(password), stdin);
        // Remove newline characters
        username[strcspn(username, "\r\n")] = 0;
        password[strcspn(password, "\r\n")] = 0;
        do_login(username, password);
    } else if (strcmp(path_info, "/secret") == 0) {
        secret_page(username);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head></head><body>");
        printf("<p>Page not found.</p>");
        printf("</body></html>\n");
    }

    return 0;
}