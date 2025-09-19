#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Password: <input type=\"password\" name=\"password\"><br>\n");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>\n");
        printf("<p>Invalid credentials.</p>\n");
        printf("</body></html>\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        login();
        return 0;
    }

    const char *path = argv[1];
    if (strcmp(path, "/login") == 0) {
        login();
    } else if (strcmp(path, "/do_login") == 0 && argc >= 4) {
        do_login(argv[2], argv[3]);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>\n");
        printf("<p>Not Found</p>\n");
        printf("</body></html>\n");
    }

    return 0;
}