#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef struct {
    char *username;
} Session;

Session session = { .username = NULL };

void free_session() {
    if (session.username) {
        free(session.username);
        session.username = NULL;
    }
}

void set_session_username(const char *username) {
    free_session();
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
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome!</h1>");
    printf("<p><a href=\"/login\">Login</a></p>");
    printf("</body></html>");
}

void secret_page() {
    if (session.username == NULL) {
        printf("Location: /index\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    }
}

void login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

int main() {
    const char *request_uri = getenv("REQUEST_URI");
    const char *method = getenv("REQUEST_METHOD");

    if (strcmp(request_uri, "/index") == 0) {
        index_page();
    } else if (strcmp(request_uri, "/login") == 0) {
        login_page();
    } else if (strcmp(request_uri, "/do_login") == 0 && strcmp(method, "POST") == 0) {
        const char *content_length_str = getenv("CONTENT_LENGTH");
        int content_length = atoi(content_length_str);
        char post_data[1024] = "";
        fread(post_data, 1, content_length, stdin);

        char username[100], password[100];
        sscanf(post_data, "username=%[^&]&password=%s", username, password);

        if (do_login(username, password)) {
            printf("HTTP/1.1 302 Found\n");
            secret_page();
        } else {
            login_page();
        }
    } else if (strcmp(request_uri, "/secret") == 0) {
        printf("HTTP/1.1 302 Found\n");
        secret_page();
    } else {
        index_page();
    }

    return 0;
}