#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

Session session;

void set_session(const char *username) {
    strncpy(session.username, username, sizeof(session.username));
}

int is_logged_in() {
    return strlen(session.username) > 0;
}

const char* get_username_from_session() {
    if (is_logged_in()) {
        return session.username;
    }
    return NULL;
}

void redirect(const char *location) {
    printf("Redirecting to %s\n", location);
    // Simulate redirection by printing the new page
    if (strcmp(location, "/secret") == 0) {
        secret_page();
    } else if (strcmp(location, "/login") == 0) {
        login_page();
    }
}

void index_page() {
    printf("Index Page\n");
    printf("<a href='/login'>Login</a>\n");
}

void login_page() {
    char username[MAX_USERNAME_LENGTH], password[50];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        set_session(username);
        redirect("/secret");
    } else {
        printf("Invalid credentials. Please try again.\n");
        login_page();
    }
}

void secret_page() {
    if (!is_logged_in()) {
        printf("Unauthorized access!\n");
        redirect("/login");
        return;
    }

    printf("Secret Settings Page\n");
    printf("Welcome, %s! This is the secret page.\n", get_username_from_session());
}

int main() {
    const char *path = "/";

    if (strcmp(path, "/") == 0) {
        index_page();
    } else if (strcmp(path, "/login") == 0) {
        login_page();
    } else if (strcmp(path, "/secret") == 0) {
        secret_page();
    }

    return 0;
}