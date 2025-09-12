#include <stdio.h>
#include <string.h>

#define MAX_SESSION_LENGTH 256

typedef struct {
    char username[MAX_SESSION_LENGTH];
} Session;

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int do_login(Session *session, const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(session->username, username, MAX_SESSION_LENGTH - 1);
        session->username[MAX_SESSION_LENGTH - 1] = '\0';
        return 1;
    }
    return 0;
}

void login_page() {
    printf("Login Page\n");
    printf("<form action='/login' method='post'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
}

void index_page() {
    printf("Index Page\n");
    printf("<a href='/login'>Login</a>\n");
}

void secret_page(Session *session) {
    if (strlen(session->username) > 0) {
        printf("Secret settings\n");
    } else {
        redirect("/login");
    }
}

int main() {
    Session session = { .username = "" };
    char username[100], password[100];

    // Simulating request handling
    const char *request_path = "/index"; // Change to simulate different pages

    if (strcmp(request_path, "/index") == 0) {
        index_page();
    } else if (strcmp(request_path, "/login") == 0) {
        login_page();

        // Simulate user input for login
        strcpy(username, "admin");
        strcpy(password, "password123");

        if (do_login(&session, username, password)) {
            redirect("/secret");
        } else {
            printf("Invalid credentials\n");
        }
    } else if (strcmp(request_path, "/secret") == 0) {
        secret_page(&session);
    }

    return 0;
}