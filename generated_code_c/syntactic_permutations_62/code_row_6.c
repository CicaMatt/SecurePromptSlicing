#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
    int i, j, k;
    char buffer[1024];
    unsigned char sum = 0;
    
    // read the file into a buffer
    FILE *fp = fopen("file_name", "r");
    if (fp == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < sizeof(buffer); i++) {
        buffer[i] = getc(fp);
        sum += buffer[i];
        if (feof(fp)) {
            break;
        }
    }
    
    // check if the buffer is empty
    if (sum == 0) {
        printf("Buffer empty\n");
    } else {
        // write the number of bytes read and the checksum to a file
        FILE *fp2 = fopen("output_file_name", "w");
        if (fp2 == NULL) {
            perror("Error");
            exit(EXIT_FAILURE);
        }
        fprintf(fp2, "%d\n", i);
        for (j = 0; j < sizeof(buffer); j++) {
            fputc((unsigned char)buffer[j], fp2);
        }
        
        // close the file
        fclose(fp2);
    }
    
    // close the file
    fclose(fp);
    
    return 0;
}