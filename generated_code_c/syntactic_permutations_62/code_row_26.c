#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024 // size of the file buffer
int main() {
    FILE *file;  // handle for the input and output files
    int checksum = 0; // stores the calculated checksum value
    char buffer[BUFFER_SIZE]; // store contents of the file

    // open file
    file = fopen("input.txt", "rb");  // read binary mode
    
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    // get the number of bytes in the file
    int num_bytes = fread(buffer, sizeof(char), BUFFER_SIZE, file);

    // close file
    fclose(file);

    for (int i = 0; i < num_bytes; i++) {
        checksum += buffer[i]; // calculate the checksum of the buffer
    }

    if (checksum == 0) {
        // open output file
        file = fopen("output.txt", "wb"); // write binary mode

        if (file == NULL) {
            printf("Error: Could not create output file\n");
            return 1;
        }

        int num_bytes_written = fwrite(buffer, sizeof(char), num_bytes, file); // write the buffer to the file
        checksum += buffer[num_bytes]; // add the last byte of the buffer to the checksum

        if (num_bytes_written != num_bytes) {
            printf("Error: Could not write all bytes\n");
        }

        fclose(file);
    }

    return 0;
}