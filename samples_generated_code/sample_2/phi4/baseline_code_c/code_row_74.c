#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGES_FOLDER "./images/"
#define BUFFER_SIZE 1024

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File not found or cannot be opened.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char buffer[BUFFER_SIZE];
    while (file_size > 0 && !feof(file)) {
        size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
        fwrite(buffer, 1, bytes_read, stdout);
        file_size -= bytes_read;
    }

    fclose(file);
}

void check_and_send_file(const char *url_path) {
    if (strncmp(url_path, "/images/", 8) == 0) {
        char filepath[BUFFER_SIZE];
        snprintf(filepath, sizeof(filepath), "%s%s", IMAGES_FOLDER, url_path + 8);

        struct stat st;
        if (stat(filepath, &st) == 0 && S_ISREG(st.st_mode)) {
            send_file_to_browser(filepath);
        } else {
            printf("File does not exist.\n");
        }
    } else {
        printf("Invalid URL path. Only /images/ paths are supported.\n");
    }
}

int main() {
    char url_path[BUFFER_SIZE];
    printf("Enter the URL path to check: ");
    fgets(url_path, BUFFER_SIZE, stdin);
    url_path[strcspn(url_path, "\n")] = '\0'; // Remove trailing newline

    check_and_send_file(url_path);

    return 0;
}