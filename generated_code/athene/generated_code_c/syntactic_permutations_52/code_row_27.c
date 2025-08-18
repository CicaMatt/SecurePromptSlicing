#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef struct {
    char *username;
} Session;

Session session = {NULL};

void set_session(char *username) {
    if (session.username != NULL) free(session.username);
    session.username = strdup(username);
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        set_session(username);
        return 1;
    }
    return 0;
}

void show_index() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    if (session.username != NULL) {
        printf("Secret settings<br>");
        printf("Welcome, %s!", session.username);
    } else {
        printf("Please log in to access the secret page.");
    }
    printf("</body></html>");
}

void show_login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'></form>");
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");

    if (strcmp(request_method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[1024];
        fread(buffer, 1, content_length, stdin);
        char username[100], password[100];
        sscanf(buffer, "username=%[^&]&password=%s", username, password);

        if (do_login(username, password)) {
            printf("Location: /index\n");
        } else {
            show_login_form();
        }
    } else {
        if (session.username != NULL) {
            show_index();
        } else {
            show_login_form();
        }
    }

    return 0;
}