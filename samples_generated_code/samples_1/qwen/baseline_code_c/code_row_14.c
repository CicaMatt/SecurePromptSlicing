#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1;
    }
    return 0;
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
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

void secret_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main(void) {
    char* request_method = getenv("REQUEST_METHOD");

    if (request_method == NULL || strcmp(request_method, "GET") == 0) {
        index_page();
    } else if (strcmp(request_method, "POST") == 0) {
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];

        int content_length = atoi(getenv("CONTENT_LENGTH"));
        int i = 0;
        while (i < content_length && getchar() != '=') i++;
        for (i = 0; i < MAX_USERNAME_LENGTH - 1 && i < content_length; i++) {
            int c = getchar();
            if (c == '&') break;
            username[i] = c;
        }
        username[i] = '\0';

        while (i < content_length && getchar() != '=') i++;
        for (i = 0; i < MAX_PASSWORD_LENGTH - 1 && i < content_length; i++) {
            int c = getchar();
            if (c == '&' || c == '\n') break;
            password[i] = c;
        }
        password[i] = '\0';

        if (do_login(username, password)) {
            printf("Location: /secret_page.cgi\n\n");
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<h1>Invalid username or password</h1>");
            printf("<a href=\"/login.html\">Try again</a>");
            printf("</body></html>");
        }
    }

    return 0;
}