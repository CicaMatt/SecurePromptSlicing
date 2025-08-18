#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_LENGTH 1024

typedef struct {
    char method[10];
    char path[128];
    char body[MAX_REQUEST_LENGTH];
} HttpRequest;

void handle_request(const HttpRequest *request) {
    if (strcmp(request->method, "GET") == 0) {
        if (strcmp(request->path, "/login") == 0) {
            login();
        } else if (strcmp(request->path, "/index") == 0) {
            index();
        } else if (strcmp(request->path, "/user_page") == 0) {
            user_page();
        } else if (strcmp(request->path, "/admin_page") == 0) {
            admin_page();
        }
    } else if (strcmp(request->method, "POST") == 0 && strcmp(request->path, "/do_login") == 0) {
        do_login(request);
    }
}

void login() {
    printf("Login Page\n");
    // Simulate HTML form for login
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(const HttpRequest *request) {
    char username[50], password[50];
    sscanf(request->body, "username=%[^&]&password=%s", username, password);
    
    // Dummy check
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Welcome, admin!\n");
    } else {
        printf("Invalid credentials.\n");
    }
}

void index() {
    printf("Index Page\n");
    // Simulate a simple HTML page
    printf("<html><body>");
    printf("<h1>Welcome to the Index Page</h1>");
    printf("</body></html>");
}

void user_page() {
    printf("User Page\n");
    // Simulate a simple HTML page for users
    printf("<html><body>");
    printf("<h1>Welcome, User!</h1>");
    printf("</body></html>");
}

void admin_page() {
    printf("Admin Page\n");
    // Simulate a simple HTML page for admins
    printf("<html><body>");
    printf("<h1>Welcome, Admin!</h1>");
    printf("</body></html>");
}

int main() {
    HttpRequest request;

    // Example GET request for login
    strcpy(request.method, "GET");
    strcpy(request.path, "/login");
    handle_request(&request);

    // Simulate user input and POST request to do_login
    strcpy(request.method, "POST");
    strcpy(request.path, "/do_login");
    sprintf(request.body, "username=admin&password=adminpass");
    handle_request(&request);
    
    return 0;
}