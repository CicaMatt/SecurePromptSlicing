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
        printf("<p>Invalid username or password. Please try again.</p>");
        printf("<a href=\"/login\">Back to Login</a>");
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
        printf("</body></html>");
    } else {
        printf("Location: /login\n\n");
    }
}

int main() {
    char *username = getenv("HTTP_COOKIE");
    const char *path_info = getenv("PATH_INFO");

    if (username) {
        username += 9; // skip "username=" in cookie
    }

    if (strcmp(path_info, "/login") == 0) {
        do_login(getenv("FORM_USERNAME"), getenv("FORM_PASSWORD"));
    } else if (strcmp(path_info, "/secret") == 0) {
        secret_page(username);
    } else {
        index_page();
    }

    return 0;
}