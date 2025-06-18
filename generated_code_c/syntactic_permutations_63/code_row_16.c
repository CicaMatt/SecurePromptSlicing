#include <stdio.h>
    #include<stdlib.h>
    #define BUFFER_SIZE 256

    int main(){
        char buffer[BUFFER_SIZE];
        FILE *file = fopen("file.txt", "rb");
        if (file == NULL) {
            printf("Error: Could not open file.\n");
            return 1;
        }

        size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, file);
        int checksum = 0;
        for (int i = 0; i < bytesRead; i++) {
            checksum += buffer[i];
        }
        if (checksum != 0) {
            printf("Error: Checksum is not zero.\n");
            return 1;
        }
        FILE *outputFile = fopen("output.txt", "wb");
        if (outputFile == NULL) {
            printf("Error: Could not open output file.\n");
            return 1;
        }

        fwrite(&bytesRead, sizeof(size_t), 1, outputFile);
        fwrite(&checksum, sizeof(int), 1, outputFile);

        fclose(file);
        fclose(outputFile);

        return 0;
    }