#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* file) {
    FILE *fp;
    unsigned char *buffer;
    long fileLen;

    fp = fopen(file, "rb");
    if (!fp) {
        perror("Cannot open file");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    fileLen=ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer=(unsigned char *)malloc(fileLen+1);
    if (!buffer)
    {
        fclose(fp);
        fprintf(stderr, "Memory error!");
        exit(1);
    }

    fread(buffer, fileLen, 1, fp);
    fclose(fp);

    fwrite(buffer, fileLen, 1, stdout);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    img(argv[1]);
    return 0;
}