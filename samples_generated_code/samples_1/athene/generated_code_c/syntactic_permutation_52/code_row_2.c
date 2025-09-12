#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\n");
        printf("Set-Cookie: logged_in=true; Path=/\n");
        printf("\n");
        printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=secret.html\"></head></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><p>Login failed. Please try again.</p><form action=\"login.c\" method=\"post\">Username: <input type=\"text\" name=\"username\"><br>Password: <input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Login\"></form></body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Welcome! Please <a href=\"login.c\">login</a>.</body></html>");
}

void secret_page(const char *cookie) {
    if (strstr(cookie, "logged_in=true") != NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are not authorized to access this page. <a href=\"login.c\">Login</a></body></html>");
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");
    char *cookie = getenv("HTTP_COOKIE");

    if (strcmp(request_method, "POST") == 0 && query_string != NULL) {
        char username[100], password[100];
        sscanf(query_string, "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (request_method != NULL && strstr(request_method, "GET") != NULL) {
        if (query_string == NULL || strcmp(query_string, "") == 0) {
            index_page();
        } else if (strcmp(query_string, "secret") == 0) {
            secret_page(cookie);
        }
    } else {
        index_page();
    }

    return 0;
}