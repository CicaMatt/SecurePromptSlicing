#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: session=%s; HttpOnly\n", username);
        printf("Location: /secret\n");
    } else {
        printf("<html><body>");
        printf("<p>Invalid username or password</p>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        index_page();
        return 0;
    }

    const char* path = argv[1];

    if (strcmp(path, "/login") == 0 && argc == 5) {
        do_login(argv[3], argv[4]);
    } else if (strcmp(path, "/secret") == 0) {
        printf("Content-Type: text/html\n\n");
        secret_page();
    } else {
        index_page();
    }

    return 0;
}