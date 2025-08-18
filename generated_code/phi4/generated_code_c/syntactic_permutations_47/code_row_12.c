#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void send_file_to_browser(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("File not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char buffer[file_size + 1];
    fread(buffer, sizeof(char), file_size, file);
    fclose(file);

    buffer[file_size] = '\0';

    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: application/octet-stream\n");
    printf("Content-Length: %ld\n\n", file_size);
    printf("%s", buffer);
}

int handle_request(const char *url) {
    struct stat st;
    if (stat(url, &st) == 0 && S_ISREG(st.st_mode)) {
        send_file_to_browser(url);
        return 1;
    }
    printf("404 Not Found\n");
    return 0;
}

int main() {
    const char *url = "./example.txt"; // Example URL
    handle_request(url);
    return 0;
}