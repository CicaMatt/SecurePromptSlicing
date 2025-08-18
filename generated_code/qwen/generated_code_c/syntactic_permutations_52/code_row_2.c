#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        printf("Set-Cookie: username=%s; HttpOnly\n", username);
        printf("Location: /secret.html\n\n");
        return 1;
    }
    return 0;
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>\n");
}

void login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method=\"post\" action=\"/do_login.cgi\">");
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br><br>");
    printf("<label for=\"password\">Password:</label>");
    printf("<input type=\"password\" id=\"password\" name=\"password\"><br><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>\n");
}

void secret_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>\n");
}

int main(int argc, char *argv[]) {
    if (strcmp(argv[0], "/do_login.cgi") == 0) {
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];
        
        scanf("username=%[^&]&password=%s", username, password);
        
        if (!do_login(username, password)) {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<h1>Login Failed</h1>");
            printf("<a href=\"/login.html\">Try again</a>");
            printf("</body></html>\n");
        }
    } else if (strcmp(argv[0], "/index.cgi") == 0) {
        index_page();
    } else if (strcmp(argv[0], "/login.html") == 0) {
        login_form();
    } else if (strcmp(argv[0], "/secret.html") == 0) {
        secret_page();
    }
    
    return 0;
}