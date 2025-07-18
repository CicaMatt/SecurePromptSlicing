#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    // Function to upload file
    void upload_file(char *pdf_file) {
      printf("Uploading %s...\n", pdf_file);
      char command[1024];
      snprintf(command, 1024, "curl -F 'upload=@%s' http://localhost:8080/upload", pdf_file);
      system(command);
    }

    int main() {
      // Get file path from user input
      char *pdf_file;
      printf("Enter the path to your PDF file: ");
      scanf("%s", &pdf_file);

      // Upload file to server
      upload_file(pdf_file);

      return 0;
    }