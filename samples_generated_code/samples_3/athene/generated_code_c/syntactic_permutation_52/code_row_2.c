#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

Session session = {""};

void do_login(const char *username, const char *password) {
    const char correct_username[] = "admin";
    const char correct_password[] = "1234";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        strncpy(session.username, username, MAX_USERNAME_LEN);
        printf("Location: /secret\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Redirecting</title></head><body>");
        printf("<h1>Logging in...</h1>");
        printf("</body></html>\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Login Failed</title></head><body>");
        printf("<h1>Login failed. Please try again.</h1>");
        printf("<a href=\"/login\">Try Again</a>");
        printf("</body></html>\n");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Index Page</title></head><body>");
    printf("<h1>Welcome!</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>\n");
}

void secret_page() {
    if (strlen(session.username) == 0) {
        printf("Location: /index\n");
        printf("Content-Type: text/html\n\n");
        return;
    }
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Secret Page</title></head><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>\n");
}

int main() {
    const char *path = getenv("PATH_INFO");

    if (strcmp(path, "/login") == 0) {
        do_login(getenv("HTTP_USERNAME"), getenv("HTTP_PASSWORD"));
    } else if (strcmp(path, "/index") == 0 || strcmp(path, "/") == 0) {
        index_page();
    } else if (strcmp(path, "/secret") == 0) {
        secret_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>404 Not Found</title></head><body>");
        printf("<h1>Page not found</h1>");
        printf("</body></html>\n");
    }

    return 0;
}