#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy structures to mimic HTTP requests and responses
typedef struct {
    char method[10];
    char path[100];
} HttpRequest;

typedef struct {
    char status_code[4];
    char body[256];
} HttpResponse;

// Function prototypes
void login(HttpRequest *request, HttpResponse *response);
void do_login(HttpRequest *request, HttpResponse *response);
void index(HttpRequest *request, HttpResponse *response);
void user_page(HttpRequest *request, HttpResponse *response);

int main() {
    // Example usage
    HttpRequest request;
    HttpResponse response;

    strcpy(request.method, "GET");
    strcpy(request.path, "/login");
    login(&request, &response);
    printf("Login Response: %s\n", response.body);

    strcpy(request.method, "POST");
    strcpy(request.path, "/do_login");
    do_login(&request, &response);
    printf("Do Login Response: %s\n", response.body);

    strcpy(request.method, "GET");
    strcpy(request.path, "/");
    index(&request, &response);
    printf("Index Response: %s\n", response.body);

    strcpy(request.method, "GET");
    strcpy(request.path, "/user_page");
    user_page(&request, &response);
    printf("User Page Response: %s\n", response.body);

    return 0;
}

void login(HttpRequest *request, HttpResponse *response) {
    if (strcmp(request->method, "GET") == 0 && strcmp(request->path, "/login") == 0) {
        strcpy(response->status_code, "200");
        strcpy(response->body, "Login Page");
    }
}

void do_login(HttpRequest *request, HttpResponse *response) {
    if (strcmp(request->method, "POST") == 0 && strcmp(request->path, "/do_login") == 0) {
        // Simulate login logic
        strcpy(response->status_code, "200");
        strcpy(response->body, "Login Successful");
    }
}

void index(HttpRequest *request, HttpResponse *response) {
    if (strcmp(request->method, "GET") == 0 && strcmp(request->path, "/") == 0) {
        strcpy(response->status_code, "200");
        strcpy(response->body, "Welcome to the Index Page");
    }
}

void user_page(HttpRequest *request, HttpResponse *response) {
    if (strcmp(request->method, "GET") == 0 && strcmp(request->path, "/user_page") == 0) {
        strcpy(response->status_code, "200");
        strcpy(response->body, "User Page Content");
    }
}