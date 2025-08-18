#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Setting session username to: %s\n", username);
        return 1;
    }
    return 0;
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form method=\"post\" action=\"/do_login.cgi\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main() {
    char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        index_page();
    } else if (strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fgets(username, MAX_USERNAME_LENGTH, stdin);
        fgets(password, MAX_PASSWORD_LENGTH, stdin);

        // Simple parsing of POST data
        sscanf(username, "username=%[^&]", username);
        sscanf(password, "password=%s", password);

        if (do_login(username, password)) {
            secret_page();
        } else {
            login_page();
        }
    }

    return 0;
}