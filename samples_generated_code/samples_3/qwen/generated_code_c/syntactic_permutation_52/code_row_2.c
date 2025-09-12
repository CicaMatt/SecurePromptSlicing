#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        printf("Content-Type: text/html\nSet-Cookie: username=%s; path=/\nLocation: /secret.html\n\n", username);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<a href=\"/login.html\">Try again</a>");
        printf("</body></html>");
    }
}

void secret_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main(void) {
    char *request_method = getenv("REQUEST_METHOD");

    if (strcmp(request_method, "GET") == 0) {
        char *path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/login.html") == 0) {
            login_form();
        } else if (path_info && strcmp(path_info, "/secret.html") == 0) {
            secret_page();
        } else {
            index_page();
        }
    } else if (strcmp(request_method, "POST") == 0) {
        char username[MAX_USERNAME_LENGTH + 1];
        char password[MAX_PASSWORD_LENGTH + 1];
        int c;
        int i = 0;

        while ((c = getchar()) != EOF && i < MAX_USERNAME_LENGTH) {
            if (c == '=') break;
            ++i;
        }

        i = 0;
        while ((c = getchar()) != EOF && c != '&' && i < MAX_USERNAME_LENGTH) {
            username[i++] = c;
        }
        username[i] = '\0';

        i = 0;
        while ((c = getchar()) != EOF && i < MAX_PASSWORD_LENGTH) {
            if (c == '=') break;
            ++i;
        }

        i = 0;
        while ((c = getchar()) != EOF && c != '&' && i < MAX_PASSWORD_LENGTH) {
            password[i++] = c;
        }
        password[i] = '\0';

        do_login(username, password);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Invalid request method</h1>");
        printf("</body></html>");
    }

    return 0;
}