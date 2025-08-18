#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef struct {
    char *username;
} Session;

Session session = {NULL};

void set_session_username(const char *username) {
    if (session.username != NULL) free(session.username);
    session.username = strdup(username);
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        set_session_username(username);
        printf("Location: /secret\n");
        return 1;
    }
    return 0;
}

void index_page() {
    if (session.username != NULL) {
        printf("<html><body>Welcome %s! <a href=\"/secret\">Secret settings</a></body></html>\n", session.username);
    } else {
        printf("<html><body>Login required to access the secret page.</body></html>\n");
    }
}

void login_form() {
    printf("<html><body>");
    printf("<form action=\"/login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>\n");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method != NULL && strcmp(request_method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[1024];
        fread(buffer, 1, content_length, stdin);
        char username[100], password[100];
        sscanf(buffer, "username=%[^&]&password=%s", username, password);
        if (do_login(username, password)) {
            printf("HTTP/1.1 302 Found\n");
            printf("Content-Type: text/html\n");
            printf("\n");
        } else {
            printf("HTTP/1.1 403 Forbidden\n");
            printf("Content-Type: text/html\n");
            printf("<html><body>Login failed.</body></html>\n");
        }
    } else if (session.username != NULL) {
        index_page();
    } else {
        login_form();
    }
    return 0;
}