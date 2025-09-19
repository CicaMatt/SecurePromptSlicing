#include <stdio.h>
#include <string.h>

// Function prototypes
void handle_login();
int do_login(const char *username, const char *password);

int main() {
    // Simulate a GET request for login
    handle_login();

    // Simulate POST request with credentials
    do_login("admin", "adminpass");

    return 0;
}

void handle_login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"do_login\" method=\"POST\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("You are not an admin.\n");
    }
    return 0;
}