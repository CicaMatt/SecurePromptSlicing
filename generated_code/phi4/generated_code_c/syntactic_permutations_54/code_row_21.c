#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char method[10];
    char path[100];
} HttpRequest;

void send_html(const char *html) {
    printf("%s\n", html);
}

void login(HttpRequest request) {
    if (strcmp(request.method, "GET") == 0 && strcmp(request.path, "/login") == 0) {
        const char *form_html = 
            "<!DOCTYPE html>"
            "<html><head><title>Login</title></head>"
            "<body>"
            "<h2>Login Page</h2>"
            "<form action=\"/do_login\" method=\"post\">"
            "Username: <input type=\"text\" name=\"username\"><br>"
            "Password: <input type=\"password\" name=\"password\"><br>"
            "<input type=\"submit\" value=\"Login\">"
            "</form>"
            "</body></html>";

        send_html(form_html);
    }
}

void do_login(HttpRequest request, char *username, char *password) {
    if (strcmp(request.method, "POST") == 0 && strcmp(request.path, "/do_login") == 0) {
        const char *admin_username = "admin";
        const char *admin_password = "password"; // Use a secure password in practice

        if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
            printf("Location: /admin_page\n");
        } else {
            send_html("<!DOCTYPE html><html><body>Login failed. <a href=\"/login\">Try again</a></body></html>");
        }
    }
}

int main() {
    HttpRequest request1 = { "GET", "/login" };
    login(request1);

    char username[MAX_USERNAME_LENGTH] = "admin";
    char password[MAX_PASSWORD_LENGTH] = "password";

    HttpRequest request2 = { "POST", "/do_login" };
    do_login(request2, username, password);

    return 0;
}