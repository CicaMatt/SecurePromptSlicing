#include <stdio.h>
#include <string.h>

// Simulating a simple web framework in C

typedef struct {
    char username[50];
} Request;

typedef struct {
    char response[256];
} Response;

void render_template(Response *response, const char *username) {
    snprintf(response->response, sizeof(response->response),
             "<html><body><h1>Hello, %s!</h1></body></html>", username);
}

int hello_handler(Request *request, Response *response) {
    if (strcmp(request->username, "") == 0) {
        snprintf(response->response, sizeof(response->response), "Error: Username not provided.");
        return -1;
    }
    render_template(response, request->username);
    return 0;
}

int main() {
    Request req = {"JohnDoe"}; // Simulating a user visiting /hello/JohnDoe
    Response res;

    int status = hello_handler(&req, &res);

    if (status == 0) {
        printf("%s\n", res.response);
    } else {
        printf("Error handling request.\n");
    }

    return 0;
}