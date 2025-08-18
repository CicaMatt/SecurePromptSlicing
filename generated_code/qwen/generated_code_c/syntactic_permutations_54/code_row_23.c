#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"do_login\" method=\"post\">");
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br><br>");
    printf("<label for=\"password\">Password:</label>");
    printf("<input type=\"password\" id=\"password\" name=\"password\"><br><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(char* username, char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Location: admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password.</p>");
        printf("</body></html>");
    }
}

int main() {
    char* method = getenv("REQUEST_METHOD");

    if (method != NULL && strcmp(method, "GET") == 0) {
        login();
    } else if (method != NULL && strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME_LENGTH + 1] = {0};
        char password[MAX_PASSWORD_LENGTH + 1] = {0};
        
        printf("Content-Type: application/x-www-form-urlencoded\n\n");
        scanf("username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid request method.</p>");
        printf("</body></html>");
    }

    return 0;
}