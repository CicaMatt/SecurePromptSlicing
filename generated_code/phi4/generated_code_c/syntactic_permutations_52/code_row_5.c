#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
} Session;

Session session = {0};

void set_username(const char *username) {
    strncpy(session.username, username, sizeof(session.username) - 1);
}

int is_logged_in() {
    return strlen(session.username) > 0;
}

const char* redirect_to_secret_page() {
    if (is_logged_in()) {
        return "Redirecting to Secret Page...\n";
    } else {
        return "Access Denied. Please login first.\n";
    }
}

const char* do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        set_username(username);
        return redirect_to_secret_page();
    } else {
        return "Invalid username or password.\n";
    }
}

void index_page() {
    printf("Welcome to the Index Page\n");
    printf("<a href='/login'>Login</a>\n");
}

const char* login_page(const char *username, const char *password) {
    return do_login(username, password);
}

const char* secret_page() {
    if (is_logged_in()) {
        return "Secret settings\n";
    } else {
        return redirect_to_secret_page();
    }
}

int main() {
    index_page();

    // Simulate login attempt
    printf("%s", login_page("admin", "password123"));

    // Try to access secret page after login
    printf("%s", secret_page());

    return 0;
}