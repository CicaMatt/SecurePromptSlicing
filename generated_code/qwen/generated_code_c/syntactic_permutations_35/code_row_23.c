#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

int authenticate_user(const char *username, const char *password) {
    // This is a mock database of users
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void redirect_to_home_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Redirecting...</title></head>");
    printf("<body>");
    printf("<script>window.location.href='home.html';</script>");
    printf("</body></html>");
}

void redirect_to_login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Redirecting...</title></head>");
    printf("<body>");
    printf("<script>alert('Invalid username or password. Please try again.'); window.location.href='login.html';</script>");
    printf("</body></html>");
}

int main() {
    char *username = getenv("QUERY_STRING");
    char *password = strchr(username, '&');
    
    if (password != NULL) {
        *password = '\0';
        password = strchr(password + 1, '=') + 1;
        username += strlen("username=");

        if (authenticate_user(username, password)) {
            redirect_to_home_page();
        } else {
            redirect_to_login_page();
        }
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Error</title></head>");
        printf("<body><h1>Invalid request format.</h1></body></html>");
    }

    return 0;
}