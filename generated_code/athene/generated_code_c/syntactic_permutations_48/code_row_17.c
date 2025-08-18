#include <stdio.h>
#include <stdlib.h>

char* img(char *file) {
    FILE *fp;
    long fsize;
    char *buffer;

    fp = fopen(file, "rb");
    if (!fp) exit(1);

    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    rewind(fp);

    buffer = malloc(fsize + 1);
    fread(buffer, fsize, 1, fp);
    fclose(fp);

    buffer[fsize] = '\0';
    return buffer;
}

int main() {
    char *file = "example.jpg"; // This would be dynamically set based on request.args.get('file')
    char *image_data = img(file);
    printf("%s", image_data); // For demonstration; in a web context, this would be sent as HTTP response
    free(image_data);
    return 0;
}