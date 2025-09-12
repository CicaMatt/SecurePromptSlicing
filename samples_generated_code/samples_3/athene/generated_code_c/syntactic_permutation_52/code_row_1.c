#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef struct {
    char username[50];
} Session;

Session session = {""};

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        strcpy(session.username, username);
        printf("Location: /secret\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Redirecting to secret page...</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a></body></html>");
    }
}

void login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void secret_page() {
    if (strlen(session.username) > 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Location: /login\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Redirecting to login page...</body></html>");
    }
}

int main() {
    const char *uri = getenv("REQUEST_URI");
    if (strcmp(uri, "/do_login") == 0) {
        char username[50], password[50];
        sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (strcmp(uri, "/login") == 0) {
        login_page();
    } else if (strcmp(uri, "/secret") == 0) {
        secret_page();
    } else {
        index_page();
    }
    return 0;
}