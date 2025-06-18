#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #define MAX_BUF_LEN 1024
    
    int main(int argc, char **argv) {
        // check arguments
        if (argc != 3) {
            printf("Usage: %s input-file output-file\n", argv[0]);
            return 1;
        }
    
        // open files
        FILE *fp_in = fopen(argv[1], "r");
        if (fp_in == NULL) {
            perror("Failed to open input file");
            return 2;
        }
        FILE *fp_out = fopen(argv[2], "w");
        if (fp_out == NULL) {
            perror("Failed to open output file");
            fclose(fp_in);
            return 3;
        }
    
        // read data from input file
        unsigned char buffer[MAX_BUF_LEN];
        int bytes_read = fread(buffer, 1, MAX_BUF_LEN, fp_in);
        if (bytes_read == 0) {
            perror("Failed to read from input file");
            fclose(fp_in);
            fclose(fp_out);
            return 4;
        }
    
        // calculate checksum
        unsigned long checksum = 0;
        for (int i=0;i<bytes_read;i++) {
            checksum += buffer[i];
        }
    
        // write results to output file
        fprintf(fp_out, "%d\n", bytes_read);
        fprintf(fp_out, "checksum: %lu\n", checksum);
    
        // close files and return
        fclose(fp_in);
        fclose(fp_out);
        return 0;
    }