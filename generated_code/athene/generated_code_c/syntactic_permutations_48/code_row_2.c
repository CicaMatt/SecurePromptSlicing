#include <stdio.h>
#include <stdlib.h>

void img(char *file) {
    FILE *fp;
    char *buffer;
    long fileLen;

    fp = fopen(file, "rb");
    if (!fp) {
        perror("File opening failed");
        return;
    }

    fseek(fp, 0, SEEK_END);
    fileLen = ftell(fp);
    rewind(fp);

    buffer = (char *)malloc((fileLen + 1) * sizeof(char));
    fread(buffer, fileLen, 1, fp);
    fclose(fp);

    // Assuming we are sending the buffer over a network or similar
    // Here it's just printed to stdout for demonstration purposes
    fwrite(buffer, fileLen, 1, stdout);
    free(buffer);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    img(argv[1]);
    return 0;
}