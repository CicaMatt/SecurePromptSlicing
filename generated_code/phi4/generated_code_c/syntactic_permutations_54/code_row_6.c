#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void send_header(const char *header) {
    printf("%s\n", header);
}

void get_login_form() {
    send_header("HTTP/1.1 200 OK");
    send_header("Content-Type: text/html");
    send_header("\n");

    printf("<html><body>");
    printf("<form method='POST' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        send_header("HTTP/1.1 302 Found");
        send_header("Location: /admin_page");
        send_header("\n");
        printf("<html><body>");
        printf("Redirecting to admin page...");
        printf("</body></html>");
    } else {
        send_header("HTTP/1.1 200 OK");
        send_header("Content-Type: text/html");
        send_header("\n");

        printf("<html><body>");
        printf("<h2>Access Denied</h2>");
        printf("</body></html>");
    }
}

int main() {
    char method[BUFFER_SIZE], path[BUFFER_SIZE];

    // Simulate reading HTTP request line
    fgets(method, BUFFER_SIZE, stdin);
    fgets(path, BUFFER_SIZE, stdin);

    if (strncmp(method, "GET ", 4) == 0 && strcmp(path, "/login\n") == 0) {
        get_login_form();
    } else if (strncmp(method, "POST /do_login", 15) == 0) {
        char username[BUFFER_SIZE], password[BUFFER_SIZE];

        // Simulate reading headers
        fgets(NULL, BUFFER_SIZE, stdin); // Skip Content-Length header

        // Simulate reading body
        scanf("username=%s&password=%s", username, password);

        do_login(username, password);
    }

    return 0;
}