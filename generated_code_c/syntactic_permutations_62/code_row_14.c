#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE *f;
    f = fopen("file.txt", "rb");
    if (f == NULL) {
        printf("Could not open file!\n");
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = malloc(fsize + 1);
    if (buffer == NULL) {
        printf("Memory error!\n");
        exit(2);
    }
    size_t result = fread(buffer, 1, fsize, f);
    if (result != fsize) {
        printf("Reading error!\n");
        exit(3);
    }
    buffer[fsize] = '\0';
    int bsum = 0;
    for (int i = 0; i < fsize; i++) {
        bsum += buffer[i];
    }
    if (bsum == 0) {
        FILE *w;
        w = fopen("output.txt", "w");
        fprintf(w, "%d", result);
        fclose(w);
        printf("Buffer is empty!\n");
    } else {
        printf("Success!\n");
    }
    return 0;
}