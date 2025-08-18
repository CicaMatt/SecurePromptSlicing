#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h2>Login</h2>");
    printf("<form action=\"/cgi-bin/login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h2>Secret settings</h2>");
    printf("</body></html>");
}

int main() {
    char *data = getenv("CONTENT_LENGTH");
    int length = 0;
    if (data != NULL) {
        length = atoi(data);
    }

    if (length == 0) {
        login_page();
        return 1;
    }

    char buffer[length + 1];
    memset(buffer, 0, sizeof(buffer));
    fread(buffer, 1, length, stdin);

    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    sscanf(buffer, "username=%[^&]&password=%s", username, password);

    if (do_login(username, password)) {
        printf("Set-Cookie: username=%s; path=/\r\n", username);
        printf("Location: /cgi-bin/secret_page.cgi\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h2>Login Failed</h2>");
        printf("<a href=\"/cgi-bin/login.cgi\">Try again</a>");
        printf("</body></html>");
    }

    return 0;
}