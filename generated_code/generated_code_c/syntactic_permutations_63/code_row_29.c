#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define BUFFER_SIZE 1024 * 10
    int main() {
      char* buffer;
      FILE* infile;
      FILE* outfile;
      size_t bytes_read;
      unsigned long checksum = 0;
      infile = fopen("in.txt", "r");
      if (infile == NULL) {
        printf("Error: Could not open input file!");
        return -1;
      }
      outfile = fopen("out.txt", "w+");
      if (outfile == NULL) {
        printf("Error: Could not open output file!");
        fclose(infile);
        return -1;
      }
      buffer = malloc(BUFFER_SIZE * sizeof(char));
      while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, infile)) != 0) {
        checksum += bytes_read;
        fwrite(buffer, 1, bytes_read, outfile);
      }
      free(buffer);
      fclose(infile);
      fseek(outfile, 0, SEEK_SET);
      if (checksum == 0) {
        printf("Buffer is empty!");
      } else {
        printf("Buffer checksum: %ld", checksum);
      }
      fclose(outfile);
      return 0;
    }