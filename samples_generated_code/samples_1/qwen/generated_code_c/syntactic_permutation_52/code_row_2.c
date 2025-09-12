#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
} Session;

void do_login(char *username, char *password, Session *session) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(session->username, username, MAX_USERNAME);
        printf("Location: /secret\n\n");
    } else {
        printf("<html><body>");
        printf("<p>Invalid username or password. <a href=\"/login\">Try again</a></p>");
        printf("</body></html>\n");
    }
}

void index_page() {
    printf("<html><body>");
    printf("<h1>Welcome to the Homepage</h1>");
    printf("<p><a href=\"/login\">Login here</a></p>");
    printf("</body></html>\n");
}

void login_page() {
    printf("<html><body>");
    printf("<h2>Login Page</h2>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>\n");
}

void secret_page(Session *session) {
    if (strlen(session->username) > 0) {
        printf("<html><body>");
        printf("<h1>Secret Settings</h1>");
        printf("<p>Welcome, %s!</p>", session->username);
        printf("</body></html>\n");
    } else {
        printf("Location: /login\n\n");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    char *script_name = getenv("SCRIPT_NAME");

    Session session;
    memset(&session, 0, sizeof(session));

    if (strcmp(script_name, "/index") == 0 || script_name == NULL) {
        index_page();
    } else if (strcmp(script_name, "/login") == 0) {
        login_page();
    } else if (strcmp(script_name, "/do_login") == 0) {
        char username[MAX_USERNAME], password[MAX_PASSWORD];
        if (method && strcmp(method, "POST") == 0) {
            int content_length = atoi(getenv("CONTENT_LENGTH"));
            char *data = malloc(content_length + 1);
            fread(data, 1, content_length, stdin);
            data[content_length] = '\0';

            sscanf(data, "username=%[^&]&password=%s", username, password);
            free(data);

            do_login(username, password, &session);
        }
    } else if (strcmp(script_name, "/secret") == 0) {
        secret_page(&session);
    }

    return 0;
}