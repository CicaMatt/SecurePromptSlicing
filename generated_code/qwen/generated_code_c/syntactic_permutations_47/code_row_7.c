#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define WEB_ROOT "./images/"
#define MAX_PATH 1024

void send_file_to_browser(const char *filename) {
    FILE *file;
    char path[MAX_PATH];
    
    snprintf(path, sizeof(path), "%s%s", WEB_ROOT, filename);
    
    struct stat file_stat;
    if (stat(path, &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }
    
    file = fopen(path, "rb");
    if (!file) {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nError opening file.\n");
        return;
    }
    
    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", file_stat.st_size);
    
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }
    
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    send_file_to_browser(argv[1]);
    
    return 0;
}