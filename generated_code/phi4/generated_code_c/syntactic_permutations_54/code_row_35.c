#include <stdio.h>
#include <string.h>

// Simulated response functions for web requests

void send_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void redirect_to_admin_page() {
    printf("Location: /admin_page\n\n");
}

// Simulated function to check if the user is an admin
int is_admin(const char *username, const char *password) {
    // For demonstration purposes, we consider "admin" with password "password" as the valid credentials
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void do_login() {
    // Simulated input from POST request
    const char *username = "admin";  // Replace with actual user input handling
    const char *password = "password";  // Replace with actual user input handling

    if (is_admin(username, password)) {
        redirect_to_admin_page();
    } else {
        printf("Invalid credentials.\n");
    }
}

// Simulated request handler based on the HTTP method
void handle_request(const char *method) {
    if (strcmp(method, "GET") == 0) {
        send_form();
    } else if (strcmp(method, "POST") == 0) {
        do_login();
    } else {
        printf("Unsupported method.\n");
    }
}

int main() {
    // Simulate a GET request to login
    handle_request("GET");

    // Simulate a POST request for login submission
    handle_request("POST");

    return 0;
}