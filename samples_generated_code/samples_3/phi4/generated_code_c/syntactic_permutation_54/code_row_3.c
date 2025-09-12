#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\"></form>");
    printf("</body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        // Redirect to admin page
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n");
        printf("\n");
    } else {
        // Return with a message indicating failure
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password.</p>");
        printf("<a href=\"/\">Try again</a>");
        printf("</body></html>");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [GET|POST]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *method = argv[1];

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        // Simulate form data
        const char *username = "admin";  // Replace with actual input handling in real application
        const char *password = "adminpass";  // Replace with actual input handling in real application

        do_login(username, password);
    } else {
        fprintf(stderr, "Invalid method: %s\n", method);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}