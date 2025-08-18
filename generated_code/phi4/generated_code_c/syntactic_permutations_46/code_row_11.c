#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t length;
} HttpResponse;

HttpResponse open_image(const char *name) {
    FILE *file = fopen(name, "rb");
    if (!file) {
        return (HttpResponse){.data = NULL, .length = 0};
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(fsize + 1);
    if (!buffer) {
        fclose(file);
        return (HttpResponse){.data = NULL, .length = 0};
    }

    fread(buffer, 1, fsize, file);
    buffer[fsize] = '\0';
    
    fclose(file);

    HttpResponse response;
    response.data = buffer;
    response.length = fsize;

    return response;
}

void send_response(HttpResponse *response) {
    printf("Content-Type: image/jpeg\n");
    printf("\n"); // HTTP/1.1 requires an extra newline after headers
    if (response->data && response->length > 0) {
        fwrite(response->data, 1, response->length, stdout);
        free(response->data);
    }
}

void img(const char *url) {
    const char *prefix = "/images/";
    size_t prefix_len = strlen(prefix);

    if (strncmp(url, prefix, prefix_len) == 0) {
        char *filename = strdup(url + prefix_len);
        HttpResponse response = open_image(filename);
        send_response(&response);
        free(filename);
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("\n");
        printf("404 Not Found");
    }
}

int main() {
    const char *url = "/images/example.jpg"; // Simulate a URL input
    img(url);

    return 0;
}