#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 100

typedef struct {
    char url[MAX_URL_LENGTH];
} Request;

void handle_request(Request *request, const char *expected_url) {
    if (strcmp(request->url, expected_url) == 0) {
        printf("Function triggered for URL: %s\n", request->url);
        // Function logic here
    } else {
        printf("URL does not match. Expected: %s, Got: %s\n", expected_url, request->url);
    }
}

#define route(url) handle_request(request, url)

int main() {
    Request request;
    strcpy(request.url, "/home");

    // Simulating a decorator-like behavior
    route("/home");  // This should trigger the function
    route("/about"); // This should not trigger the function

    return 0;
}