#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Location: /secret\n");
        printf("Set-Cookie: username=%s\n", username);
        printf("\n");
        printf("<html><body>Redirecting to secret page...</body></html>\n");
    } else {
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a></body></html>\n");
    }
}

void index_page() {
    printf("<html><body>Welcome! <a href=\"/login\">Login here</a></body></html>\n");
}

void secret_page(const char *username) {
    if (strcmp(username, USERNAME) == 0) {
        printf("<html><body>Secret settings</body></html>\n");
    } else {
        printf("Location: /index\n");
        printf("\n");
        printf("<html><body>You are not authorized to view this page. <a href=\"/login\">Login here</a></body></html>\n");
    }
}

int main() {
    const char *request_uri = getenv("REQUEST_URI");
    const char *username_cookie = getenv("HTTP_COOKIE");

    if (request_uri == NULL) request_uri = "/index";

    if (strcmp(request_uri, "/login") == 0) {
        printf("<html><body>");
        printf("<form method=\"post\" action=\"/do_login\">");
        printf("Username: <input type=\"text\" name=\"username\"><br>");
        printf("Password: <input type=\"password\" name=\"password\"><br>");
        printf("<input type=\"submit\" value=\"Login\">");
        printf("</form></body></html>\n");
    } else if (strcmp(request_uri, "/do_login") == 0) {
        char username[100], password[100];
        size_t content_length = atol(getenv("CONTENT_LENGTH"));
        fread(username, 1, sizeof(username) - 1, stdin);
        fread(password, 1, sizeof(password) - 1, stdin);
        sscanf(username, "username=%[^&]", username);
        sscanf(password, "&password=%s", password);
        do_login(username, password);
    } else if (strcmp(request_uri, "/secret") == 0) {
        char username[100] = "";
        if (username_cookie != NULL) {
            sscanf(username_cookie, "username=%[^;]", username);
        }
        secret_page(username);
    } else {
        index_page();
    }

    return 0;
}