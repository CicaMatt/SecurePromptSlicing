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
        printf("<html><body>You are not authorized to access this page. Redirecting...</body></html>\n");
    }
}

int main() {
    const char *request = getenv("REQUEST_URI");
    const char *username_cookie = getenv("HTTP_COOKIE");

    if (request == NULL) request = "/index";

    if (strcmp(request, "/login") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<form method=\"post\" action=\"/do_login\">");
        printf("Username: <input type=\"text\" name=\"username\"><br>");
        printf("Password: <input type=\"password\" name=\"password\"><br>");
        printf("<input type=\"submit\" value=\"Login\"></form>");
        printf("</body></html>\n");
    } else if (strcmp(request, "/do_login") == 0) {
        const char *username = getenv("HTTP_X_USERNAME");
        const char *password = getenv("HTTP_X_PASSWORD");
        do_login(username, password);
    } else if (strcmp(request, "/secret") == 0) {
        printf("Content-Type: text/html\n\n");
        secret_page(strstr(username_cookie, "username=") + 9);
    } else {
        printf("Content-Type: text/html\n\n");
        index_page();
    }

    return 0;
}