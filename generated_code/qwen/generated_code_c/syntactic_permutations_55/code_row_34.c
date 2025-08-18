#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mocking HTTP server functions and structures

typedef struct {
    char *method;
    char *path;
    char *body;
} HttpRequest;

typedef struct {
    int status_code;
    char *content_type;
    char *body;
} HttpResponse;

void send_response(HttpResponse response) {
    printf("Status Code: %d\n", response.status_code);
    printf("Content-Type: %s\n", response.content_type);
    printf("Body: %s\n", response.body);
}

HttpResponse handle_request(HttpRequest request) {
    if (strcmp(request.method, "GET") == 0 && strcmp(request.path, "/login") == 0) {
        return login(request);
    } else if (strcmp(request.method, "POST") == 0 && strcmp(request.path, "/do_login") == 0) {
        return do_login(request);
    } else if (strcmp(request.method, "GET") == 0 && strcmp(request.path, "/index") == 0) {
        return index_page(request);
    } else if (strcmp(request.method, "GET") == 0 && strcmp(request.path, "/user_page") == 0) {
        return user_page(request);
    } else if (strcmp(request.method, "GET") == 0 && strcmp(request.path, "/admin_page") == 0) {
        return admin_page(request);
    } else {
        HttpResponse response = {404, "text/plain", "Not Found"};
        return response;
    }
}

HttpResponse login(HttpRequest request) {
    HttpResponse response = {200, "text/html", "<html><body><form action='/do_login' method='post'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit' value='Login'></form></body></html>"};
    return response;
}

HttpResponse do_login(HttpRequest request) {
    // Simple mock authentication
    if (strstr(request.body, "username=admin&password=secret")) {
        HttpResponse response = {200, "text/plain", "Login successful"};
        return response;
    } else {
        HttpResponse response = {401, "text/plain", "Unauthorized"};
        return response;
    }
}

HttpResponse index_page(HttpRequest request) {
    HttpResponse response = {200, "text/html", "<html><body><h1>Welcome to the Index Page</h1></body></html>"};
    return response;
}

HttpResponse user_page(HttpRequest request) {
    HttpResponse response = {200, "text/html", "<html><body><h1>User Page</h1></body></html>"};
    return response;
}

HttpResponse admin_page(HttpRequest request) {
    HttpResponse response = {200, "text/html", "<html><body><h1>Admin Page</h1></body></html>"};
    return response;
}

int main() {
    // Simulating a GET request to /login
    HttpRequest login_request = {"GET", "/login", NULL};
    HttpResponse login_response = handle_request(login_request);
    send_response(login_response);

    // Simulating a POST request to /do_login with correct credentials
    HttpRequest do_login_request_correct = {"POST", "/do_login", "username=admin&password=secret"};
    HttpResponse do_login_response_correct = handle_request(do_login_request_correct);
    send_response(do_login_response_correct);

    // Simulating a POST request to /do_login with incorrect credentials
    HttpRequest do_login_request_incorrect = {"POST", "/do_login", "username=user&password=wrong"};
    HttpResponse do_login_response_incorrect = handle_request(do_login_request_incorrect);
    send_response(do_login_response_incorrect);

    // Simulating a GET request to /index
    HttpRequest index_request = {"GET", "/index", NULL};
    HttpResponse index_response = handle_request(index_request);
    send_response(index_response);

    // Simulating a GET request to /user_page
    HttpRequest user_page_request = {"GET", "/user_page", NULL};
    HttpResponse user_page_response = handle_request(user_page_request);
    send_response(user_page_response);

    // Simulating a GET request to /admin_page
    HttpRequest admin_page_request = {"GET", "/admin_page", NULL};
    HttpResponse admin_page_response = handle_request(admin_page_request);
    send_response(admin_page_response);

    return 0;
}