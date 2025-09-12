#include <stdio.h>
#include <string.h>

// Mock functions to simulate HTTP behavior
void send_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void redirect_to_admin() {
    printf("HTTP/1.1 302 Found\nLocation: /admin_page\n\n");
}

// Simulated function to handle GET request for login
void login_get_request() {
    send_form();
}

// Function to check credentials and perform login logic
void do_login_post_request(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) { // Example admin credentials
        redirect_to_admin();
    } else {
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h2>Login failed</h2>");
        printf("</body></html>");
    }
}

// Simulated main function to handle requests
int main() {
    char request_type[10];
    scanf("%s", request_type);

    if (strcmp(request_type, "GET") == 0) {
        login_get_request();
    } else if (strcmp(request_type, "POST") == 0) {
        char username[50], password[50];
        printf("Enter username: ");
        scanf("%49s", username);
        printf("Enter password: ");
        scanf("%49s", password);

        do_login_post_request(username, password);
    }

    return 0;
}