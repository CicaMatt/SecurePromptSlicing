#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void send_header(const char *header) {
    printf("%s\n", header);
}

void img(FILE *file, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    send_header("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n");

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    
    fclose(fp);
}

int main() {
    send_header("HTTP/1.1 200 OK\r\n");
    send_header("Content-Type: text/html; charset=utf-8\r\n");

    printf("<html><body>\n"
           "<h1>Image Gallery</h1>\n"
           "<img src=\"http://localhost/img/image.jpg\">\n"
           "</body></html>\n");

    // Simulating a request to the /img URL
    printf("Request: GET /img HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");
    
    img(NULL, "image.jpg");  // Replace 'image.jpg' with actual image file path

    return 0;
}