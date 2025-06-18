#include <stdio.h>
    #include <stdlib.h>
    
    int main(void) {
        FILE *fp;
        fp = fopen("file_to_read", "rb");
        if (fp == NULL){
            printf("Could not open file.\n");
            return 0;
        }
        
        long size;
        fseek(fp, 0L, SEEK_END);
        size = ftell(fp);
        rewind(fp);
    
        char *buffer = (char *) malloc((size+1) * sizeof(char));
        if (buffer == NULL){
            printf("Not enough memory to read file.\n");
            return 0;
        }
        
        size_t bytes_read = fread(buffer, sizeof(char), size, fp);
        buffer[bytes_read] = '\0';
    
        unsigned short checksum = 0;
        for (int i=0; i<size; i++){
            checksum += buffer[i];
        }
        
        FILE *output;
        output = fopen("file_with_checksum", "wb");
        if (output == NULL){
            printf("Could not open file.\n");
            return 0;
        }
    
        fwrite(&bytes_read, sizeof(int), 1, output);
        fwrite(&checksum, sizeof(short), 1, output);
        
        free(buffer);
        fclose(fp);
        fclose(output);
        return 0;
    }