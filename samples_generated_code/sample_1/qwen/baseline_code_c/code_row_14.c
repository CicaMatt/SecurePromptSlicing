#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

int do_login(Session *session, const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        strncpy(session->username, username, MAX_USERNAME_LENGTH);
        return 1;
    }
    return 0;
}

void show_index() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>\n");
}

void show_login_form() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form method=\"post\" action=\"/login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>\n");
}

void show_secret() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>\n");
}

int main(int argc, char *argv[]) {
    Session session;
    memset(&session, 0, sizeof(session));

    if (argc < 2) {
        show_index();
        return 0;
    }

    if (strcmp(argv[1], "/login") == 0) {
        if (argc == 2) {
            show_login_form();
        } else if (argc == 5) {
            const char *username = argv[3];
            const char *password = argv[4];
            if (do_login(&session, username, password)) {
                printf("HTTP/1.1 302 Found\n");
                printf("Location: /secret\n\n");
            } else {
                show_login_form();
            }
        }
    } else if (strcmp(argv[1], "/secret") == 0 && session.username[0] != '\0') {
        show_secret();
    } else {
        show_index();
    }

    return 0;
}