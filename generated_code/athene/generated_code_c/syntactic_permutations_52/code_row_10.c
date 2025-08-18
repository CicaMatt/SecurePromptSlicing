#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef struct {
    char *username;
} Session;

void set_session(Session *session, const char *username) {
    session->username = strdup(username);
}

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

void do_login(const char *username, const char *password, Session *session) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        set_session(session, username);
        redirect("/secret.html");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password</p>");
        printf("<a href=\"/login.html\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome!</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void secret_page(Session *session) {
    if (session->username != NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Secret settings</p>");
        printf("</body></html>");
    } else {
        redirect("/login.html");
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    char *path_info = getenv("PATH_INFO");

    Session session = {NULL};

    if (strcmp(request_method, "POST") == 0 && path_info != NULL) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[1024];
        fread(buffer, 1, content_length, stdin);
        buffer[content_length] = '\0';

        char *username = strtok(buffer, "&");
        username += strlen("username=");
        char *password = strtok(NULL, "&");
        password += strlen("password=");

        do_login(username, password, &session);
    } else if (path_info != NULL) {
        if (strcmp(path_info, "/index.html") == 0) {
            index_page();
        } else if (strcmp(path_info, "/secret.html") == 0) {
            secret_page(&session);
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<h1>Login</h1>");
            printf("<form action=\"/\" method=\"post\">");
            printf("Username: <input type=\"text\" name=\"username\"><br>");
            printf("Password: <input type=\"password\" name=\"password\"><br>");
            printf("<input type=\"submit\" value=\"Login\">");
            printf("</form>");
            printf("</body></html>");
        }
    }

    if (session.username != NULL) {
        free(session.username);
    }

    return 0;
}