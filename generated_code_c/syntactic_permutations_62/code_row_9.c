#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    unsigned char* read_file(const char *filename) {
        FILE *fp;
        size_t fsize = 0;
        unsigned char *buf;
    
        fp = fopen(filename, "rb"); // open the file in binary mode
        if (!fp)
            return NULL; // return NULL on error
        
        // get the file size
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
    
        buf = malloc((fsize + 1) * sizeof(*buf)); // allocate memory for buffer
        if (!buf) {
            fclose(fp);
            return NULL; // return NULL on error
        }
        
        memset(buf, '\0', fsize); // zero out the buffer
    
        fseek(fp, 0, SEEK_SET); // reset pointer to start of file
        if (fread(buf, fsize, 1, fp) != 1) {
            free(buf);
            fclose(fp);
            return NULL; // return NULL on error
        }
    
        fclose(fp); // close the file
        
        return buf;
    }
    
    int calculate_checksum(unsigned char *buffer) {
        int checksum = 0;
        
        for (int i = 0; i < strlen((char *)buffer); i++) {
            checksum += buffer[i];
        }
        
        return checksum;
    }
    
    void write_file(const char *filename, int bytes, int checksum) {
        FILE *fp;
        
        fp = fopen(filename, "w"); // open the file in write mode
        if (!fp)
            return; // return on error
        
        fprintf(fp, "%d %d", bytes, checksum); // write to the file
    
        fclose(fp); // close the file
    }
    
    int main(int argc, char **argv) {
        unsigned char *buffer;
        int bytes = 0;
        int checksum = 0;
        
        if (argc != 3)
            return EXIT_FAILURE; // exit on error
        
        buffer = read_file(argv[1]); // read the file
        if (!buffer) {
            free(buffer);
            return EXIT_FAILURE; // exit on error
        }
    
        bytes = strlen((char *)buffer); // get the number of bytes read
        
        checksum = calculate_checksum(buffer); // calculate the checksum
        
        write_file(argv[2], bytes, checksum); // write to the file
    
        free(buffer); // free the memory
        
        return EXIT_SUCCESS;
    }