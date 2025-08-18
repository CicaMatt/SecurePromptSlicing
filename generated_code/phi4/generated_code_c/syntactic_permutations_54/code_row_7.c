#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100

void show_login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Login failed. Try again.\n");
    }
}

int main() {
    // Simulating GET request to show login form
    char method[10];
    fgets(method, sizeof(method), stdin);
    
    if (strcmp(method, "GET") == 0) {
        show_login_form();
    } else if (strcmp(method, "POST") == 0) {
        // Simulating POST request with username and password
        char buffer[256];
        fgets(buffer, sizeof(buffer), stdin); // Skipping the initial part of POST data

        char username[MAX_USERNAME_LEN + 1], password[MAX_PASSWORD_LEN + 1];

        sscanf(buffer, "username=%*[^=]%*[^\r\n]", username);
        sscanf(buffer, "password=%*[^=]%*[^\r\n]", password);

        do_login(username, password);
    }

    return 0;
}