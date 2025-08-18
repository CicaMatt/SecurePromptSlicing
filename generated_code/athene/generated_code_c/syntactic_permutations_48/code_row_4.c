#include <stdio.h>
#include <stdlib.h>

void img(char *file) {
    FILE *fp;
    char *buffer;
    long fileLen;

    fp = fopen(file, "rb");
    if (!fp) {
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    fileLen=ftell(fp);
    rewind(fp);

    buffer=(char *)malloc((fileLen+1)*sizeof(char));
    if (buffer == NULL) {
        fclose(fp);
        exit(1);
    }

    fread(buffer, fileLen, 1, fp);
    fclose(fp);

    // Assuming this is where you would handle sending the buffer back
    // For example, in a web server context, you might write it to the response stream.
    // Here we just print the length of the data read as an indication of success.
    printf("Image file length: %ld\n", fileLen);

    free(buffer);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}