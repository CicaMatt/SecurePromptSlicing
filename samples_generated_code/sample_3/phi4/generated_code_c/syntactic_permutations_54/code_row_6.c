#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='POST' action='/do_login'>"
           "<label for='username'>Username:</label>"
           "<input type='text' id='username' name='username'><br>"
           "<label for='password'>Password:</label>"
           "<input type='password' id='password' name='password'><br><br>"
           "<input type='submit' value='Login'>"
           "</form>");
    printf("</body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        // Redirect to admin page
        printf("Location: /admin_page\n\n");
        return;
    }

    // Return a message indicating login failure
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<p>Login failed. Please try again.</p>");
    printf("</body></html>");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Handle wrong number of arguments
        return 1;
    }

    const char *method = argv[1];
    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0 && argc >= 4) {
        const char *username = argv[2];
        const char *password = argv[3];
        do_login(username, password);
    }

    return 0;
}