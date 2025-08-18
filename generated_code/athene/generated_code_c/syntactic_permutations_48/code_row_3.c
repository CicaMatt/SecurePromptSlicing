#include <stdio.h>
#include <stdlib.h>

void img(char *file) {
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, fp);
    fclose(fp);
    // Assuming the function to send response is implemented elsewhere
    send_response(200, "image/jpeg", buffer, fsize);
    free(buffer);
}

int main() {
    char *file = "example.jpg"; // This would be dynamically set based on request.args.get('file')
    img(file);
    return 0;
}