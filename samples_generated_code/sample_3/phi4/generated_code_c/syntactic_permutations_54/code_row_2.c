#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char username[50];
    char password[50];

    // Simulate reading POST data
    if (sscanf(getenv("QUERY_STRING"), "username=%49[^&]&password=%49s", username, password) == 2) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            printf("Location: /admin_page\n\n");
        } else {
            printf("Invalid credentials. Please try again.\n");
        }
    } else {
        printf("Error in form submission.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <request_type>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "GET") == 0) {
        login();
    } else if (strcmp(argv[1], "POST") == 0) {
        do_login();
    } else {
        fprintf(stderr, "Invalid request type.\n");
        return 1;
    }

    return 0;
}