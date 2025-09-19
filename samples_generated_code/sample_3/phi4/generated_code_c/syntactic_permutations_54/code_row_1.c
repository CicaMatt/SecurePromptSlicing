#include <stdio.h>
#include <string.h>

void handle_get_request() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n"
           "<body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "  Username:<br>"
           "  <input type=\"text\" name=\"username\"><br>"
           "  Password:<br>"
           "  <input type=\"password\" name=\"password\"><br><br>"
           "  <input type=\"submit\" value=\"Login\">\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

void handle_post_request(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /admin_page\n\n");
    } else {
        printf("Login failed. Please try again.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [GET|POST username password]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "GET") == 0) {
        handle_get_request();
    } else if (strcmp(argv[1], "POST") == 0 && argc == 5) {
        const char *username = argv[2];
        const char *password = argv[3];
        handle_post_request(username, password);
    } else {
        fprintf(stderr, "Invalid usage. Expected GET or POST with username and password.\n");
        return 1;
    }

    return 0;
}