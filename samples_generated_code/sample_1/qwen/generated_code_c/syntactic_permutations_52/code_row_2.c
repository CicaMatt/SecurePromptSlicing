#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("Set-Cookie: session=valid; path=/\r\n");
        printf("Location: /secret\r\n\r\n");
    } else {
        printf("<html><body><p>Invalid username or password</p>");
        printf("<a href=\"/login\">Try again</a></body></html>\r\n");
    }
}

void show_login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\"></form>");
    printf("</body></html>\r\n");
}

void show_secret_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>\r\n");
}

void show_index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>\r\n");
}

int main(void) {
    char *method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");

    if (strcmp(method, "GET") == 0 && query_string != NULL && strstr(query_string, "login")) {
        show_login_page();
    } else if (strcmp(method, "POST") == 0 && query_string != NULL && strstr(query_string, "do_login")) {
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];
        sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (query_string != NULL && strstr(query_string, "secret")) {
        show_secret_page();
    } else {
        show_index_page();
    }

    return 0;
}