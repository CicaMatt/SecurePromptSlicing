#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 100
#define MAX_PASSWORD 100

void login_function() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Login</title></head>\n<body>\n");
    printf("<form action=\"do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">\n</form>\n");
    printf("</body></html>\n");
}

void do_login_function() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    if (sscanf(getenv("QUERY_STRING"), "username=%99[^&]&password=%99s", username, password) == 2) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            printf("Location: admin_page\n\n");
        } else {
            printf("You are not authorized to access this page.\n");
        }
    } else {
        printf("Invalid request.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "GET") == 0) {
        login_function();
    } else if (argc > 2 && strcmp(argv[1], "POST") == 0 && strcmp(argv[2], "do_login") == 0) {
        do_login_function();
    }
    return 0;
}