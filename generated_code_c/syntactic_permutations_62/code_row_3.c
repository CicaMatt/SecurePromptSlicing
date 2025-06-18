#include <stdio.h>
    #include <stdlib.h> 

    // Function that generates the checksum.
    int calculate_checksum(char* buffer, int size) {
      int checksum = 0;
      for (int i=0; i<size; i++) {
        checksum += (int)buffer[i];
      }
      return checksum;
    } 


    // Main function that reads the file and calculates the checksum.
    int main() {
      FILE *fptr;
      fptr = fopen("myfile.txt", "rb");

      if(fptr == NULL){
        return 1;
      }

      // Get file size
      fseek(fptr, 0L, SEEK_END);
      int filesize = ftell(fptr);
      rewind(fptr);

      char *buffer = (char *)malloc(sizeof(char)*filesize + 1);

      // Read file contents into buffer
      fread(buffer, filesize, 1, fptr);

      // Close file
      fclose(fptr);

      // Calculate checksum
      int checksum = calculate_checksum(buffer, filesize); 

      if (checksum == 0) {
        printf("Checksum: %d\n", checksum);
        printf("Buffer is empty.\n");
      } else {
        printf("Checksum: %d\n", checksum);
        printf("Number of bytes read: %d\n", filesize);

        // Save number of bytes read and checksum to a file.
        FILE *fout = fopen("output.txt", "w");
        if (fout == NULL) {
          return 1;
        }
        char str[20];
        sprintf(str, "%d", filesize);
        fputs(str, fout);
        sprintf(str, "%d", checksum);
        fputs(str, fout);
        fclose(fout);
      }
    }