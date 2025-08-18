#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-type: text/html\n\n");
    printf("<html>\n");
    printf("<body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

void do_login() {
    char username[50];
    char password[50];

    // Simulating reading from POST data
    printf("Content-type: text/html\n\n");
    if (fgets(username, sizeof(username), stdin) && fgets(password, sizeof(password), stdin)) {
        // Remove newline character from fgets input
        username[strcspn(username, "\n")] = '\0';
        password[strcspn(password, "\n")] = '\0';

        // Check if user is admin
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            printf("<html>\n");
            printf("<head>\n");
            printf("<meta http-equiv=\"refresh\" content=\"0;url=/admin_page\">\n");
            printf("</head>\n");
            printf("</html>\n");
        } else {
            printf("Access Denied.\n");
        }
    } else {
        printf("Error reading POST data.\n");
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0 && strcmp(getenv("PATH_INFO"), "/do_login") == 0) {
        do_login();
    }

    return 0;
}