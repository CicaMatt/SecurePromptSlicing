#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: username=%s\r\n", username);
        printf("Location: /secret\r\n");
        printf("\r\n");
        printf("<html><body>Logged in successfully. Redirecting...</body></html>");
    } else {
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><head><title>Index Page</title></head><body>");
    printf("<p>Welcome! Please <a href=\"/login\">log in</a> to access the secret page.</p>");
    printf("</body></html>");
}

void login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><head><title>Login Page</title></head><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void secret_page() {
    char username[100];
    // Simulate retrieving the username from a cookie
    strcpy(username, "admin"); // In real code, this should come from a secure session mechanism

    if (strcmp(username, USERNAME) == 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><head><title>Secret Page</title></head><body>");
        printf("<p>Secret settings</p>");
        printf("</body></html>");
    } else {
        printf("Location: /login\r\n");
        printf("\r\n");
        printf("<html><body>You are not logged in. <a href=\"/login\">Log in</a></body></html>");
    }
}

int main() {
    const char *path = getenv("PATH_INFO");
    if (strcmp(path, "/") == 0) {
        index_page();
    } else if (strcmp(path, "/login") == 0) {
        login_page();
    } else if (strcmp(path, "/do_login") == 0) {
        const char *username = getenv("HTTP_USERNAME");
        const char *password = getenv("HTTP_PASSWORD");
        do_login(username, password);
    } else if (strcmp(path, "/secret") == 0) {
        secret_page();
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>404 Not Found</body></html>");
    }
    return 0;
}