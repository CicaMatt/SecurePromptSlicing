#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

char *session_username = NULL;

void set_session(const char *username) {
    if (session_username != NULL) free(session_username);
    session_username = strdup(username);
}

int do_login(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        set_session(username);
        return 1;
    }
    return 0;
}

void show_login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Login Page</h2>");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'></form>");
    printf("</body></html>");
}

void show_secret_page() {
    if (session_username == NULL) {
        printf("Location: /login\n");
        return;
    }
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Secret settings</h2>");
    printf("<p>Welcome, %s!</p>", session_username);
    printf("</body></html>");
}

void show_index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Index Page</h2>");
    printf("<a href='/login'>Login</a>");
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (strcmp(request_method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[1024];
        fread(buffer, 1, content_length, stdin);
        buffer[content_length] = '\0';

        char *username = NULL;
        char *password = NULL;

        username = strstr(buffer, "username=");
        if (username) {
            username += 9; // length of "username="
            password = strstr(username, "&password=");
            if (password) {
                *password = '\0';
                password += 10; // length of "&password="
            }
        }

        if (do_login(username, password)) {
            printf("Location: /secret\n");
        } else {
            show_login_page();
        }
    } else {
        char *path_info = getenv("PATH_INFO");
        if (strcmp(path_info, "/login") == 0) {
            show_login_page();
        } else if (strcmp(path_info, "/secret") == 0) {
            show_secret_page();
        } else {
            show_index_page();
        }
    }

    return 0;
}