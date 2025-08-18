#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

Session current_session = {""};

void print_html_header(const char *title) {
    printf("Content-Type: text/html\n\n");
    printf("<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<title>%s</title>\n</head>\n<body>\n", title);
}

void print_html_footer() {
    printf("</body>\n</html>");
}

void index_page() {
    print_html_header("Home");
    printf("<h1>Welcome to the Home Page</h1>\n");
    printf('<a href="login.html">Login</a>');
    print_html_footer();
}

void login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        fgets(username, MAX_USERNAME_LENGTH, stdin);
        username[strcspn(username, "\r\n")] = '\0';
        fgets(password, MAX_PASSWORD_LENGTH, stdin);
        password[strcspn(password, "\r\n")] = '\0';

        if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
            strncpy(current_session.username, username, sizeof(current_session.username));
            printf("HTTP/1.1 302 Found\nLocation: /secret.html\n\n");
        } else {
            print_html_header("Login Failed");
            printf("<h1>Login Failed</h1>\n<p>Invalid username or password.</p>\n<a href=\"login.html\">Try again</a>");
            print_html_footer();
        }
    } else {
        print_html_header("Login");
        printf("<form method=\"POST\" action=\"/\">\n"
               "<label for=\"username\">Username:</label><br>\n"
               "<input type=\"text\" id=\"username\" name=\"username\"><br>\n"
               "<label for=\"password\">Password:</label><br>\n"
               "<input type=\"password\" id=\"password\" name=\"password\"><br><br>\n"
               "<input type=\"submit\" value=\"Submit\">\n</form>");
        print_html_footer();
    }
}

void secret_page() {
    if (strcmp(current_session.username, "") == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /login.html\n\n");
        return;
    }

    print_html_header("Secret Settings");
    printf("<h1>Secret settings</h1>");
    print_html_footer();
}

int main() {
    char *request_path = getenv("PATH_INFO");

    if (strcmp(request_path, "/") == 0) {
        index_page();
    } else if (strcmp(request_path, "/login.html") == 0 || strcmp(request_path, "/") == 0 && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        login_page();
    } else if (strcmp(request_path, "/secret.html") == 0) {
        secret_page();
    }

    return 0;
}