#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password123"

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Invalid username or password.</p>");
        printf("</body></html>");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");
    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[1024];
        fread(buffer, 1, content_length, stdin);
        buffer[content_length] = '\0';

        char *username = strstr(buffer, "username=");
        if (username != NULL) {
            username += strlen("username=");
            char *password = strstr(username, "&password=");
            if (password != NULL) {
                *password++ = '\0';
                do_login(username, password);
            }
        }
    }

    return 0;
}