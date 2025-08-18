#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n"
           "<head><title>Login</title></head>\n"
           "<body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "  Username: <input type=\"text\" name=\"username\"><br>\n"
           "  Password: <input type=\"password\" name=\"password\"><br>\n"
           "  <input type=\"submit\" value=\"Login\">\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /admin_page\n\n");
    } else {
        printf("Invalid credentials.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <method> <username> [password]\n", argv[0]);
        return 1;
    }

    const char *method = argv[1];
    const char *username = argv[2];
    const char *password = argc > 3 ? argv[3] : "";

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0 && username != NULL && password != NULL) {
        do_login(username, password);
    } else {
        fprintf(stderr, "Invalid method or missing parameters.\n");
        return 1;
    }

    return 0;
}