#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\n");
        printf("Set-Cookie: username=%s; Path=/\n", username);
        printf("Location: /secret\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password</p>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome!</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void secret_page(const char *username) {
    if (strcmp(username, USERNAME) == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("<p>Welcome %s!</p>", username);
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>You are not authorized to view this page.</p>");
        printf("<a href=\"/login\">Login</a>");
        printf("</body></html>");
    }
}

int main() {
    const char *request_uri = getenv("REQUEST_URI");
    const char *username = getenv("HTTP_COOKIE");

    if (request_uri == NULL || strcmp(request_uri, "/") == 0) {
        index_page();
    } else if (strcmp(request_uri, "/login") == 0) {
        const char *form_data = getenv("QUERY_STRING");
        char username[100], password[100];
        sscanf(form_data, "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (strcmp(request_uri, "/secret") == 0) {
        secret_page(username ? strstr(username, "username=") + 9 : "");
    }

    return 0;
}