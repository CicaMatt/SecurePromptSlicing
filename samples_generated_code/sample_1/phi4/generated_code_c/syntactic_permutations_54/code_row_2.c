#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void handle_get_request() {
    printf("Content-type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

void handle_post_request(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /admin_page.html\n\n");
    } else {
        handle_get_request();
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s METHOD [username] [password]\n", argv[0]);
        return 1;
    }

    const char *method = argv[1];
    
    if (strcmp(method, "GET") == 0) {
        handle_get_request();
    } else if (strcmp(method, "POST") == 0 && argc == 5) {
        const char *username = argv[2];
        const char *password = argv[3];
        handle_post_request(username, password);
    } else {
        fprintf(stderr, "Invalid usage.\n");
        return 1;
    }
    
    return 0;
}