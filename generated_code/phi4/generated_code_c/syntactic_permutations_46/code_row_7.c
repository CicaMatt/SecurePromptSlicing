#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *url;
    void (*func)(const char *);
} Decorator;

void send_response(FILE *file) {
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char buffer[fsize + 1];
    fread(buffer, fsize, 1, file);
    fclose(file);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Assuming JPEG for simplicity
    printf("Content-Length: %ld\r\n", fsize);
    printf("\r\n");
    fwrite(buffer, fsize, 1, stdout);
}

void img(const char *name) {
    FILE *file = fopen(name, "rb");
    send_response(file);
}

Decorator create_decorator(void (*func)(const char *)) {
    Decorator decorator;
    decorator.url = "/img";
    decorator.func = func;
    return decorator;
}

void handle_request(const char *url, const char *params) {
    if (strcmp(url, "/img") == 0) {
        img(params);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
    }
}

int main() {
    Decorator my_decorator = create_decorator(img);

    // Simulate a request
    const char *request_url = "/img";
    const char *params = "images/example.jpg"; // Example image name

    handle_request(request_url, params);

    return 0;
}


This code simulates handling an HTTP-like request to serve images. It assumes the server is running on a platform that supports standard input/output redirection for sending responses back to the client. Adjustments might be needed based on actual network programming requirements and error handling specifics.