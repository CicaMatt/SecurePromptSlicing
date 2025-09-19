#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
} Request;

typedef struct {
    const char *template;
} Response;

char* render_template(const char *filename, const char *username) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(length + strlen(username) + 100); // extra space for dynamic content
    size_t read_length = fread(buffer, 1, length, file);
    buffer[read_length] = '\0';
    fclose(file);

    char *result = malloc(strlen(buffer) + strlen(username) + 1);
    sprintf(result, buffer, username);
    free(buffer);
    return result;
}

Response* hello(Request *request) {
    Response *response = (Response*)malloc(sizeof(Response));
    response->template = render_template("hello.html", request->username);
    return response;
}

void url_map(const char *url, Request *request, Response **response) {
    if (strcmp(url, "/hello/") == 0) {
        *response = hello(request);
    }
}

int main() {
    Request request;
    request.username = "John Doe";
    Response *response = NULL;

    url_map("/hello/", &request, &response);

    if (response && response->template) {
        printf("%s\n", response->template);
        free((char*)response->template);
    }

    free(response);
    return 0;
}