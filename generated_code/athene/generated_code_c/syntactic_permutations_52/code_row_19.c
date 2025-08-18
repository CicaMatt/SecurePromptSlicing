#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void print_header() {
    printf("Content-Type: text/html\r\n\r\n");
}

void index_page() {
    print_header();
    printf("<html><body>");
    printf("<h1>Welcome!</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void login_page() {
    print_header();
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        print_header();
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        login_page();
    }
}

int main() {
    char *uri = getenv("REQUEST_URI");
    if (uri && strcmp(uri, "/login") == 0) {
        login_page();
    } else if (uri && strncmp(uri, "/do_login", 9) == 0) {
        char username[100] = "", password[100] = "";
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, sizeof(char), 100, stdin);
        sscanf(username, "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else {
        index_page();
    }
    return 0;
}