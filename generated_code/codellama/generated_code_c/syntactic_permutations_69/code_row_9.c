#include <stdio.h>
#include <string.h>

int upload_image(char *file) {
    // Read the uploaded file
    FILE *fptr;
    fptr = fopen(file, "rb");
    if (fptr == NULL) {
        printf("ERROR: Could not open %s\n", file);
        return 1;
    }
    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    rewind(fptr);
    unsigned char *bytes = malloc(size);
    if (fread(bytes, 1, size, fptr) != size) {
        printf("ERROR: Could not read %s\n", file);
        return 1;
    }
    // Encode the image in base64
    char *image = malloc(size * 2);
    memset(image, 0, size * 2);
    unsigned long len = 0;
    if (mime_encode(bytes, size, "base64", image, &len) != MIME_OK) {
        printf("ERROR: Could not encode %s\n", file);
        return 1;
    }
    // Write the encoded image to a new file
    FILE *ofile = fopen("image.b64", "w");
    if (fwrite(image, 1, len, ofile) != len) {
        printf("ERROR: Could not write %s\n", "image.b64");
        return 1;
    }
    fclose(ofile);
    return 0;
}