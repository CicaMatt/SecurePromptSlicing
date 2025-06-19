#include <stdio.h>
    #include <stdlib.h>

    int main() {
      FILE *fp;
      unsigned char buffer[1024];
      size_t bytes_read;
      unsigned short checksum = 0;

      fp = fopen("input.txt", "r");
      if (fp == NULL) {
        printf("Could not open file\n");
        return 1;
      }

      bytes_read = fread(buffer, sizeof(unsigned char), 1024, fp);
      for (int i = 0; i < bytes_read; i++) {
        checksum += buffer[i];
      }

      if (checksum == 0) {
        printf("Buffer is empty\n");
      } else {
        printf("Checksum: %d\n", checksum);
        printf("Number of bytes read: %zu\n", bytes_read);
      }

      fclose(fp);

      FILE *output;
      output = fopen("output.txt", "w");
      if (output == NULL) {
        printf("Could not open file for writing\n");
        return 1;
      }

      fprintf(output, "%zu %d", bytes_read, checksum);
      fclose(output);
    }