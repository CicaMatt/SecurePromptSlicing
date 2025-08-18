#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void send_header(FILE *fp, const char *filename) {
    fprintf(fp, "HTTP/1.0 200 OK\n");
    fprintf(fp, "Content-Type: image/*\n"); // Assuming all images are valid; adjust as necessary
    fprintf(fp, "\r\n");
}

FILE* open_image(const char *name) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "./images/%s", name);
    return fopen(filepath, "rb");
}

void img(FILE *fp, const char *url) {
    // Extract the file name from URL
    const char *filename_start = strstr(url, "/img/") + 5;
    const char *filename_end = strchr(filename_start, ' ');
    
    if (!filename_end) filename_end = url + strlen(url);
    
    size_t filename_len = filename_end - filename_start;
    if (filename_len == 0) {
        fprintf(fp, "HTTP/1.0 400 Bad Request\n");
        fprintf(fp, "\r\n");
        return;
    }
    
    char *filename = malloc(filename_len + 1);
    strncpy(filename, filename_start, filename_len);
    filename[filename_len] = '\0';

    FILE *image_file = open_image(filename);
    if (!image_file) {
        fprintf(fp, "HTTP/1.0 404 Not Found\n");
        fprintf(fp, "\r\n");
    } else {
        send_header(fp, filename);
        
        char buffer[BUFFER_SIZE];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, image_file)) > 0) {
            fwrite(buffer, 1, bytes_read, fp);
        }
        fclose(image_file);
    }

    free(filename);
}

int main() {
    FILE *fp = stdout; // Using standard output for demonstration purposes
    
    // Example URL input
    const char *url = "GET /img/example.jpg HTTP/1.1";
    
    img(fp, url);

    return 0;
}