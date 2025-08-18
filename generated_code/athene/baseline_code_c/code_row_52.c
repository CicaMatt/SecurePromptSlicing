#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\n");
        printf("Set-Cookie: username=%s; Path=/\n", username);
        printf("Location: /secret\n\n");
        printf("<html><body>Redirecting to secret page...</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Welcome! <a href=\"/login\">Login here</a></body></html>");
}

void secret_page(const char *username) {
    if (strcmp(username, USERNAME) == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are not authorized to view this page. <a href=\"/login\">Login here</a></body></html>");
    }
}

int main() {
    const char *request_uri = getenv("REQUEST_URI");
    const char *username = getenv("HTTP_COOKIE");

    if (request_uri == NULL) request_uri = "/";

    if (strcmp(request_uri, "/") == 0 || strcmp(request_uri, "/index") == 0) {
        index_page();
    } else if (strcmp(request_uri, "/login") == 0) {
        const char *post_data = getenv("POST_DATA");
        if (post_data != NULL && strlen(post_data) > 0) {
            char username[100], password[100];
            sscanf(post_data, "username=%[^&]&password=%s", username, password);
            do_login(username, password);
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body><form method=\"post\" action=\"/login\">Username: <input type=\"text\" name=\"username\"><br>Password: <input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Login\"></form></body></html>");
        }
    } else if (strcmp(request_uri, "/secret") == 0) {
        char extracted_username[100] = "";
        sscanf(username, "username=%s", extracted_username);
        secret_page(extracted_username);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>404 Not Found</body></html>");
    }

    return 0;
}