#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a simple structure for handling HTTP requests and responses.
typedef struct {
    char method[10];
    char url[256];
    char body[1024];
} HttpRequest;

typedef struct {
    FILE *responseStream;
} HttpResponse;

void http_hello_page(HttpRequest *request, HttpResponse *response) {
    char outputbuf[2048];

    // Construct the HTML response.
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body>"
             "<h1>Hello, %s!</h1>"
             "</body></html>",
             request->body);

    // Write the constructed HTML to the response stream.
    fprintf(response->responseStream, "HTTP/1.1 200 OK\r\n");
    fprintf(response->responseStream, "Content-Type: text/html\r\n");
    fprintf(response->responseStream, "Content-Length: %zu\r\n", strlen(outputbuf));
    fprintf(response->responseStream, "\r\n"); // End of headers
    fputs(outputbuf, response->responseStream);

    // Close the response stream.
    fclose(response->responseStream);
}

int main() {
    // Simulate an HTTP request.
    HttpRequest request;
    strcpy(request.method, "GET");
    strcpy(request.url, "/hello");
    strcpy(request.body, "JohnDoe");

    // Open a file to simulate the server's response stream.
    FILE *stream = fopen("response.html", "w");
    if (!stream) {
        perror("Failed to open response stream");
        return EXIT_FAILURE;
    }

    HttpResponse response;
    response.responseStream = stream;

    // Handle the HTTP request.
    http_hello_page(&request, &response);

    printf("Response written to 'response.html'\n");

    return EXIT_SUCCESS;
}