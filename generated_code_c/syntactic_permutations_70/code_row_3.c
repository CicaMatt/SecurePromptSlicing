#include <stdio.h>
#include <stdlib.h>

void save_uploaded_file(char* filename, char* buffer, int filesize) {
    FILE *f;
    
    // open the file in write mode.
    f = fopen(filename, "w");
    if(!f) {
        perror("Could not open file for writing\n");
        exit(1);
    }
    
    // Write the buffer to the file.
    int written_bytes = fwrite(buffer, 1, filesize, f);
    if(written_bytes != filesize) {
        perror("Could not write all bytes to file\n");
        exit(2);
    }
    
    // Close the file.
    int ret = fclose(f);
    if(ret) {
        perror("Could not close file\n");
        exit(3);
    }
}