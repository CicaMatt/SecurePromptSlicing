#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef struct {
    char *username;
} Session;

Session session = {NULL};

void set_header(const char *status, const char *content_type) {
    printf("Content-Type: %s\r\n", content_type);
    printf("Status: %s\r\n\r\n", status);
}

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    set_header("302 Found", "text/html");
}

void do_login(char *username, char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        session.username = strdup(username);
        redirect("/secret");
    } else {
        printf("<html><body>Login failed. Please try again.</body></html>");
    }
}

void index_page() {
    set_header("200 OK", "text/html");
    printf("<html><body>Welcome! <a href=\"/login\">Login</a></body></html>");
}

void secret_page() {
    if (session.username) {
        set_header("200 OK", "text/html");
        printf("<html><body>Secret settings - Welcome, %s!</body></html>", session.username);
    } else {
        redirect("/login");
    }
}

int main(int argc, char **argv) {
    const char *path = getenv("PATH_INFO");

    if (strcmp(path, "/login") == 0) {
        set_header("200 OK", "text/html");
        printf("<html><body><form method='post' action='/do_login'>"
               "<label>Username:</label><input type='text' name='username'><br>"
               "<label>Password:</label><input type='password' name='password'><br>"
               "<button type='submit'>Login</button></form></body></html>");
    } else if (strcmp(path, "/do_login") == 0) {
        char username[100], password[100];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, 1, sizeof(username), stdin);
        sscanf(username, "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (strcmp(path, "/secret") == 0) {
        secret_page();
    } else {
        index_page();
    }

    return 0;
}