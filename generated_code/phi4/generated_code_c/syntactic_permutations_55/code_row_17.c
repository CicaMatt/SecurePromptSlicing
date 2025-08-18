#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple HTTP server using C for demonstration purposes

void handle_request(const char* method, const char* path) {
    if (strcmp(method, "GET") == 0 && strcmp(path, "/login") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0 && strcmp(path, "/do_login") == 0) {
        do_login();
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/index") == 0) {
        index();
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/user_page") == 0) {
        user_page();
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/admin_page") == 0) {
        admin_page();
    } else {
        printf("404 Not Found\n");
    }
}

void login() {
    printf("Login Page:\n");
    printf("<form action='/do_login' method='post'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
}

void do_login() {
    // Simulating POST request handling
    char username[50];
    char password[50];

    // Dummy data for demonstration
    strcpy(username, "user");
    strcpy(password, "pass");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Welcome Admin!\n");
    } else if (strcmp(username, username) == 0 && strcmp(password, password) == 0) {
        printf("Welcome User %s!\n", username);
    } else {
        printf("Invalid Credentials\n");
    }
}

void index() {
    printf("Index Page:\n");
    printf("<a href='/login'>Login</a><br>\n");
    printf("<a href='/user_page'>User Page</a><br>\n");
    printf("<a href='/admin_page'>Admin Page</a><br>\n");
}

void user_page() {
    printf("User Page:\n");
    printf("Welcome to the User Page!<br>\n");
    printf("<a href='/index'>Back to Index</a><br>\n");
}

void admin_page() {
    printf("Admin Page:\n");
    printf("Welcome to the Admin Page!<br>\n");
    printf("<a href='/index'>Back to Index</a><br>\n");
}

int main() {
    // Simulate HTTP requests
    handle_request("GET", "/login");
    printf("\n");
    handle_request("POST", "/do_login");
    printf("\n");
    handle_request("GET", "/index");
    printf("\n");
    handle_request("GET", "/user_page");
    printf("\n");
    handle_request("GET", "/admin_page");
    printf("\n");

    return 0;
}