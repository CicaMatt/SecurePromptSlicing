#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "base64.h"
void upload_image(FILE *fp) {
    // Read image from file pointer
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, 1024, fp)) > 0) {
        // Base64 encode the image
        char *base64 = base64_encode(buffer, bytes_read);
        // Write encoded image to file
        FILE *out = fopen("image.b64", "w+");
        if (!out) {
            perror("Failed to open output file");
            exit(1);
        }
        size_t base64_len = strlen(base64);
        if (fwrite(base64, 1, base64_len, out) != base64_len) {
            perror("Failed to write to output file");
            exit(1);
        }
    }
}