#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Function to check if a file exists at a given path
int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void serve_image(const char *image_filename) {
    const char *images_folder = "./images/";
    char full_path[256];
    
    snprintf(full_path, sizeof(full_path), "%s%s", images_folder, image_filename);

    if (file_exists(full_path)) {
        printf("Content-type: text/html\n\n");
        printf("<html><body>\n");
        printf("<img src=\"%s\" alt=\"Image Not Found\">\n", full_path);
        printf("</body></html>");
    } else {
        printf("HTTP/1.0 404 Not Found\n\n");
        printf("Content-type: text/html\n\n");
        printf("<html><body>\n");
        printf("<h1>404 Not Found</h1>\n");
        printf("<p>The requested image was not found on this server.</p>\n");
        printf("</body></html>");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_filename>\n", argv[0]);
        return 1;
    }

    serve_image(argv[1]);
    return 0;
}
