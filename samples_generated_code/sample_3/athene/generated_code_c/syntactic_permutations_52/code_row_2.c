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
    // Simulate setting session
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
    printf("<p>Invalid username or password.</p>");
    printf("<a href=\"/login\">Try again</a>");
    printf("</body></html>\n");
    return 0;
}

void index() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome!</h1>");
    printf("<p><a href=\"/login\">Login</a> to access the secret settings.</p>");
    printf("</body></html>\n");
}

void login() {
    char username[256] = "", password[256] = "";
    const char *method = getenv("REQUEST_METHOD");

    if (method && strcmp(method, "POST") == 0) {
        int content_length;
        sscanf(getenv("CONTENT_LENGTH"), "%d", &content_length);
        fread(username, sizeof(char), 255, stdin);
        username[strcspn(username, "&")] = '\0'; // Remove trailing &
        sscanf(strstr(username, "password=") + 9, "%s", password);

        do_login(username, password);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login</h1>");
        printf("<form method=\"post\">");
        printf("<label for=\"username\">Username:</label>");
        printf("<input type=\"text\" id=\"username\" name=\"username\"><br>");
        printf("<label for=\"password\">Password:</label>");
        printf("<input type=\"password\" id=\"password\" name=\"password\"><br>");
        printf("<button type=\"submit\">Login</button>");
        printf("</form></body></html>\n");
    }
}

void secret() {
    const char *username = getenv("HTTP_COOKIE");
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
    const char *path_info = getenv("PATH_INFO");

    if (strcmp(path_info, "/login") == 0) {
        login();
    } else if (strcmp(path_info, "/secret") == 0) {
        secret();
    } else {
        index();
    }

    return 0;
}