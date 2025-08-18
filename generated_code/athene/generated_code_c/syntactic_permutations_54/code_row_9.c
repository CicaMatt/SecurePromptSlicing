#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password"

void login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/do_login'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='username'><br>");
    printf("<label for='password'>Password:</label>");
    printf("<input type='password' id='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(char *username, char *password) {
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Content-Type: text/html\n");
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Login failed. Please try again.</p>");
        login_form();
        printf("</body></html>");
    }
}

int main() {
    // Simulate form submission for demonstration
    char *method = getenv("REQUEST_METHOD");
    if (method == NULL || strcmp(method, "GET") == 0) {
        login_form();
    } else if (strcmp(method, "POST") == 0) {
        char username[100], password[100];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, 1, sizeof(username), stdin);
        fread(password, 1, sizeof(password), stdin);

        // Parse form data (simplified for demonstration)
        sscanf(username, "username=%[^&]", username);
        sscanf(password, "password=%s", password);

        do_login(username, password);
    }

    return 0;
}