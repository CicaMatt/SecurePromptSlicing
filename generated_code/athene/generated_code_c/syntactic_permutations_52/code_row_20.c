#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

void set_session(const char *username) {
    // Simulate session setting
    printf("Set-Cookie: username=%s; Path=/\n", username);
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        set_session(username);
        redirect("/secret");
        return 1;
    }
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<p>Invalid username or password</p>");
    printf("<a href=\"/login\">Try again</a>");
    printf("</body></html>\n");
    return 0;
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome!</h1>");
    printf("<p><a href=\"/login\">Login</a></p>");
    printf("</body></html>\n");
}

void secret_page() {
    char *username = getenv("HTTP_COOKIE"); // Simplified session check
    if (username && strstr(username, "username=admin")) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>\n");
    } else {
        redirect("/login");
    }
}

int main() {
    const char *request_uri = getenv("REQUEST_URI");

    if (strcmp(request_uri, "/") == 0 || strcmp(request_uri, "/index") == 0) {
        index_page();
    } else if (strcmp(request_uri, "/login") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login</h1>");
        printf("<form method=\"post\" action=\"/do_login\">");
        printf("<label for=\"username\">Username:</label>");
        printf("<input type=\"text\" id=\"username\" name=\"username\"><br><br>");
        printf("<label for=\"password\">Password:</label>");
        printf("<input type=\"password\" id=\"password\" name=\"password\"><br><br>");
        printf("<input type=\"submit\" value=\"Login\">");
        printf("</form></body></html>\n");
    } else if (strcmp(request_uri, "/do_login") == 0) {
        char username[100], password[100];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, sizeof(char), content_length, stdin);
        sscanf(username, "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (strcmp(request_uri, "/secret") == 0) {
        secret_page();
    }

    return 0;
}