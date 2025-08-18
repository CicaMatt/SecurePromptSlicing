#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock structure for HTTP request and response
typedef struct {
    char* method;
    char* path;
    char* body;
} HttpRequest;

typedef struct {
    int status_code;
    char* content;
} HttpResponse;

// Mock function to simulate sending an HTTP response
void send_response(HttpResponse response) {
    printf("Status Code: %d\nContent: %s\n", response.status_code, response.content);
}

// Function prototypes
HttpResponse do_login(HttpRequest request);
HttpResponse index();
HttpResponse user_page();
HttpResponse admin_page();

// Login function
void login(HttpRequest request) {
    if (strcmp(request.method, "POST") == 0 && strcmp(request.path, "/login") == 0) {
        send_response(do_login(request));
    } else {
        HttpResponse response = {405, "Method Not Allowed"};
        send_response(response);
    }
}

// Simulate a POST request to /login
HttpResponse do_login(HttpRequest request) {
    // Here you would typically parse the request body and authenticate the user
    if (strstr(request.body, "username=admin&password=secret") != NULL) {
        HttpResponse response = {200, "Login successful"};
        return response;
    } else {
        HttpResponse response = {401, "Unauthorized"};
        return response;
    }
}

// Index page function
HttpResponse index() {
    HttpResponse response = {200, "<h1>Welcome to the Home Page</h1>"};
    return response;
}

// User page function
HttpResponse user_page() {
    HttpResponse response = {200, "<h1>User Dashboard</h1>"};
    return response;
}

// Admin page function
HttpResponse admin_page() {
    HttpResponse response = {200, "<h1>Admin Dashboard</h1>"};
    return response;
}

int main() {
    // Example usage of the functions
    HttpRequest request1 = {"POST", "/login", "username=admin&password=secret"};
    login(request1);

    HttpRequest request2 = {"GET", "/", NULL};
    send_response(index());

    HttpRequest request3 = {"GET", "/user", NULL};
    send_response(user_page());

    HttpRequest request4 = {"GET", "/admin", NULL};
    send_response(admin_page());

    return 0;
}