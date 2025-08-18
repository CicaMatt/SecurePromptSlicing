#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>"
           "Username: <input type='text' name='username'><br>"
           "Password: <input type='password' name='password'><br>"
           "<input type='submit' value='Login'></form>"
           "</body></html>");
}

int authenticate(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0;
}

void do_login() {
    char username[MAX_LEN];
    char password[MAX_LEN];

    // Simulate reading data from a POST request
    printf("Content-Type: text/html\n\n");
    printf("POST Data Received:<br>");

    // In practice, you would read actual input from the user here.
    // For demonstration purposes, we will simulate this with predefined values:
    strcpy(username, "admin");  // Simulated input for username
    strcpy(password, "admin123");  // Simulated input for password

    printf("Username: %s<br>Password: %s<br>", username, password);

    if (authenticate(username, password)) {
        printf("<html><body>");
        printf("<script type='text/javascript'>"
               "window.location = '/admin_page';"
               "</script>"
               "</body></html>");
    } else {
        printf("Invalid credentials.");
    }
}

int main() {
    // Simulated request handling
    char method[MAX_LEN];
    strcpy(method, "GET");  // Change to "POST" to test do_login

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        do_login();
    }

    return 0;
}