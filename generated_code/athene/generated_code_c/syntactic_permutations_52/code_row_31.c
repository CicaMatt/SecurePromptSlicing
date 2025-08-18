#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "secret"

typedef struct {
    char *username;
} Session;

Session session = {NULL};

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        session.username = strdup(username);
        printf("Location: /secret\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Redirecting...</title></head><body onLoad=\"window.location='/secret'\"></body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><p>Login failed. <a href=\"/login\">Try again</a>.</p></body></html>");
    }
}

void show_login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Login</title></head><body>");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'></form></body></html>");
}

void show_secret_page() {
    if (session.username) {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Secret Settings</title></head><body>");
        printf("<p>Welcome, %s! Here are your <b>Secret settings</b>.</p>", session.username);
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><p>You are not logged in. <a href=\"/login\">Login here</a>.</p></body></html>");
    }
}

void handle_request(const char *uri, const char *method, const char *username, const char *password) {
    if (strcmp(uri, "/do_login") == 0 && strcmp(method, "POST") == 0) {
        do_login(username, password);
    } else if (strcmp(uri, "/login") == 0 || strcmp(uri, "/") == 0) {
        show_login_form();
    } else if (strcmp(uri, "/secret") == 0) {
        show_secret_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><p>404 - Not Found</p></body></html>");
    }
}

int main() {
    const char *uri = getenv("REQUEST_URI");
    const char *method = getenv("REQUEST_METHOD");
    const char *username = getenv("HTTP_USERNAME");
    const char *password = getenv("HTTP_PASSWORD");

    handle_request(uri, method, username, password);

    return 0;
}