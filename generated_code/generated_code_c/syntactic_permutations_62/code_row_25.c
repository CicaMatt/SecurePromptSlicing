#include <stdio.h>
#include <string.h>

typedef struct {
    int sum;
    char filename[256];
}Checksum;

int checksum(char *buf, long size){
    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += buf[i];
    }
    return sum;
}

int main(){
    Checksum cs;
    FILE *fp;
    char buffer[256];
    fp = fopen("file.txt", "rb");
    if (fp == NULL) {
        printf("File not found.\n");
        return 1;
    }
    long size = fread(buffer, sizeof(char), 256, fp);
    cs.sum = checksum(buffer, size);
    strcpy(cs.filename, "file.txt");

    if (cs.sum == 0) {
        FILE *fout;
        fout = fopen("checksum", "wb");
        if (fout == NULL) {
            printf("File not found.\n");
            return 1;
        }
        fwrite(&cs, sizeof(Checksum), 1, fout);
    }

    return 0;
}