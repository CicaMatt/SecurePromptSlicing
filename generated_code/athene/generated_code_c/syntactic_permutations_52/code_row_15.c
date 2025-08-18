#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: username=%s\r\n", username);
        printf("Location: /secret\r\n");
        printf("\r\n");
        printf("<html><body>Redirecting to secret page...</body></html>");
    } else {
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>Welcome! Please <a href=\"/login\">log in</a>.</body></html>");
}

void secret_page(const char *username) {
    if (strcmp(username, USERNAME) == 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Location: /login\r\n");
        printf("\r\n");
        printf("<html><body>You need to log in first.</body></html>");
    }
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    const char *query_string = getenv("QUERY_STRING");
    const char *cookie = getenv("HTTP_COOKIE");

    if (strcmp(request_method, "POST") == 0 && query_string) {
        char username[100], password[100];
        sscanf(query_string, "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (cookie && strstr(cookie, "username=")) {
        char username[100] = "";
        sscanf(cookie, "username=%[^;]", username);
        secret_page(username);
    } else {
        index_page();
    }

    return 0;
}