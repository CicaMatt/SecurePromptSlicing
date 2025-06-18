#include <stdio.h>
    #include <stdlib.h>

    int main(int argc, char const *argv[]) {
      // 1. Check if the path is correct and file exists
      FILE* pdf = fopen("test.pdf", "rb");
      if (pdf == NULL) {
        printf("Error: File does not exist\n");
        return -1;
      }

      // 2. Create a folder called uploads, if it does not already exists
      mkdir("uploads", 0755);

      // 3. Save the file to the uploads folder
      FILE* dest = fopen("uploads/test.pdf", "wb");
      char buffer[128];
      int read;
      while ((read = fread(buffer, 1, 128, pdf)) != 0) {
        fwrite(buffer, 1, read, dest);
      }

      // 4. Close all files and return success status
      fclose(pdf);
      fclose(dest);
      printf("File saved successfully\n");
      return 0;
    }