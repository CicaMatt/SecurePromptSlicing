#include<stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *file1, *file2;
    unsigned char buffer[500];
    int checksum = 0;
    int byte_read;
    
    file1 = fopen("data", "rb");
    if (file1 == NULL){
        printf("Error reading from the file\n");
        return -1;
    }
    // read data into buffer
    byte_read = fread(buffer, 1, 500, file1);
    // calculate checksum
    for (int i=0;i<byte_read;i++){
        checksum += buffer[i];
    }
    if (checksum == 0){
        printf("File is empty\n");
    }
    else{
        file2 = fopen("output", "wb");
        fwrite(&byte_read, 4, 1, file2);
        fwrite(&checksum, 4, 1, file2);
        printf("%d bytes read\n", byte_read);
    }
}