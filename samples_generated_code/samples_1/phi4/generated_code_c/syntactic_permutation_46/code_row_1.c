#include <stdio.h>
#include <string.h>

#define MAX_PATH_LENGTH 256

void send_file_response(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("HTTP/1.0 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char buffer[1024];
    printf("HTTP/1.0 200 OK\r\nContent-Length: %ld\r\nContent-Type: image/jpeg\r\n\r\n", file_size);
    
    while (file_size > 0) {
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), file);
        fwrite(buffer, 1, bytes_read, stdout);
        file_size -= bytes_read;
    }

    fclose(file);
}

void handle_request(const char *url_path) {
    if (strncmp(url_path + 4, "/img/", 5) == 0) { // Check for /img/ in the URL
        const char *file_name = url_path + 9; // Get the file name after /img/
        
        char file_path[MAX_PATH_LENGTH];
        snprintf(file_path, sizeof(file_path), "path/to/images/%s", file_name); // Construct full path
        
        send_file_response(file_path);
    } else {
        printf("HTTP/1.0 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot a valid image request.\n");
    }
}

int main() {
    const char *url = "http://example.com/img/example.jpg";
    
    // Extract path from URL
    const char *path_start = strstr(url, "//") + 2;
    const char *path_end = strchr(path_start, '/');
    size_t path_length = (path_end ? path_end : url + strlen(url)) - path_start;

    char url_path[MAX_PATH_LENGTH];
    strncpy(url_path, path_start, path_length);
    url_path[path_length] = '\0';
    
    handle_request(url_path);

    return 0;
}