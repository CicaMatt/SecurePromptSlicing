#include <stdio.h>
#include <string.h>

#define SESSION_SIZE 256

typedef struct {
    char username[SESSION_SIZE];
} Session;

void set_session_username(Session *session, const char *username) {
    strncpy(session->username, username, SESSION_SIZE - 1);
}

int is_logged_in(const Session *session) {
    return session->username[0] != '\0';
}

void redirect_to_secret_page() {
    printf("Redirecting to the secret page...\n");
    printf("<h1>Secret settings</h1>\n");
}

void do_login(Session *session, const char *input_username, const char *input_password) {
    if (strcmp(input_username, "admin") == 0 && strcmp(input_password, "password") == 0) {
        set_session_username(session, input_username);
        redirect_to_secret_page();
    } else {
        printf("Invalid username or password.\n");
        printf("<a href=\"index.html\">Back to login</a>\n");
    }
}

void show_index_page() {
    printf("<h1>Welcome!</h1>\n");
    printf("<p><a href=\"login.html\">Login here</a></p>\n");
}

void show_login_page(const Session *session) {
    if (is_logged_in(session)) {
        redirect_to_secret_page();
    } else {
        printf("<form method=\"post\" action=\"do_login\">\n");
        printf("Username: <input type=\"text\" name=\"username\"><br>\n");
        printf("Password: <input type=\"password\" name=\"password\"><br>\n");
        printf("<input type=\"submit\" value=\"Login\">\n");
        printf("</form>\n");
    }
}

int main() {
    Session session = {0};

    // Simulating the request handling
    char *request_page = "index";  // Change this to "login" or "do_login" to simulate different pages

    if (strcmp(request_page, "index") == 0) {
        show_index_page();
    } else if (strcmp(request_page, "login") == 0) {
        show_login_page(&session);
    } else if (strcmp(request_page, "do_login") == 0) {
        char input_username[] = "admin";  // Change these to test different inputs
        char input_password[] = "password";
        do_login(&session, input_username, input_password);
    }

    return 0;
}