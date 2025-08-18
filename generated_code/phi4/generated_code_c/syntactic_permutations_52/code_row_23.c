#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
} Session;

void start_session(Session *session, const char *username) {
    strncpy(session->username, username, sizeof(session->username));
}

int do_login(const char *input_username, const char *input_password) {
    const char correct_username[] = "user";
    const char correct_password[] = "pass";

    if (strcmp(input_username, correct_username) == 0 && strcmp(input_password, correct_password) == 0) {
        return 1;
    }
    return 0;
}

void login_page() {
    printf("Login Page:\n");
    printf("<form action='/login' method='post'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
}

void secret_page(Session *session) {
    if (strlen(session->username) > 0) {
        printf("Secret settings\n");
        printf("<a href='/login'>Logout</a>\n");
    } else {
        printf("You must be logged in to view this page.\n");
        login_page();
    }
}

int main() {
    Session session = {0};
    char input_username[50];
    char input_password[50];

    // Simulate user input for testing
    strcpy(input_username, "user");
    strcpy(input_password, "pass");

    printf("Attempting to log in...\n");
    if (do_login(input_username, input_password)) {
        start_session(&session, input_username);
        printf("Login successful!\n");
    } else {
        printf("Login failed. Incorrect username or password.\n");
        login_page();
    }

    secret_page(&session);

    return 0;
}