#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate HTTP request handling
void handle_request(const char *method, const char *path) {
    if (strcmp(method, "GET") == 0 && strcmp(path, "/login") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0 && strcmp(path, "/do_login") == 0) {
        do_login();
    }
}

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login() {
    char username[256], password[256];
    
    // Simulate reading form data
    printf("Content-Type: text/plain\n\n");
    printf("Username=admin&Password=secret");  // Example input, replace with actual handling

    sscanf(getenv("QUERY_STRING"), "Username=%255[^&]&Password=%255s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Login failed.\n");
    }
}

int main() {
    // Simulate an incoming GET request
    handle_request("GET", "/login");

    // Simulate an incoming POST request
    const char *env_query_string = "Username=admin&Password=secret";  // Example input, replace with actual handling
    setenv("QUERY_STRING", env_query_string, 1);
    handle_request("POST", "/do_login");

    return 0;
}