#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='POST' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char username[MAX_INPUT_SIZE];
    char password[MAX_INPUT_SIZE];

    // Simulate reading POST data
    printf("Content-Type: text/html\n\n");

    if (fgets(username, sizeof(username), stdin) && fgets(password, sizeof(password), stdin)) {
        // Remove newline character from fgets input
        size_t len;
        username[len = strlen(username) - 1] = '\0';
        if (username[len] == '\n') username[len] = '\0';

        password[len = strlen(password) - 1] = '\0';
        if (password[len] == '\n') password[len] = '\0';

        // Check credentials
        if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
            printf("<html><body>");
            printf("Redirecting to admin page...");
            printf("</body></html>");
        } else {
            printf("<html><body>");
            printf("Login failed.");
            printf("</body></html>");
        }
    } else {
        printf("<html><body>");
        printf("Error reading input.");
        printf("</body></html>");
    }
}

int main() {
    char method[MAX_INPUT_SIZE];
    
    // Simulate HTTP request handling
    printf("Content-Type: text/plain\n\n");
    if (fgets(method, sizeof(method), stdin)) {
        method[strcspn(method, "\r\n")] = '\0'; // Remove newline character

        if (strcmp(method, "GET") == 0) {
            login();
        } else if (strcmp(method, "POST") == 0) {
            do_login();
        } else {
            printf("Unsupported method.");
        }
    }

    return 0;
}
