#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database check for username and password.
int check_credentials(const char *username, const char *password) {
    // For demonstration purposes, we'll assume these are valid credentials.
    return strcmp(username, "user") == 0 && strcmp(password, "pass");
}

void redirect_to_home() {
    printf("HTTP/1.1 302 Found\r\nLocation: /home.html\r\n\r\n");
    exit(0);
}

void redirect_to_login() {
    printf("HTTP/1.1 302 Found\r\nLocation: /login.html\r\n\r\n");
    exit(0);
}

int main() {
    // Simulating reading from a POST request
    char method[10], path[100];
    scanf("%s %s", method, path);

    if (strcmp(method, "POST") == 0 && strcmp(path, "/login") == 0) {
        char username[50], password[50];

        // Read the content length from headers and then read the POST data
        char line[100];
        fgets(line, sizeof(line), stdin); // Reading Content-Length header

        int content_length = atoi(strtok(line, " "));
        char post_data[content_length + 1];
        fread(post_data, 1, content_length, stdin);

        sscanf(post_data, "username=%49[^&]&password=%49s", username, password);

        if (check_credentials(username, password)) {
            redirect_to_home();
        } else {
            redirect_to_login();
        }
    }

    // Default to returning login page on any other request
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form action='/login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");

    return 0;
}