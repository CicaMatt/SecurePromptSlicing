#include <stdio.h>
    #include <stdlib.h>
    #include "base64.h"

    int upload_image() {
      FILE *fptr;
      char *filepath = "/path/to/uploaded/image.jpg";
      fptr = fopen(filepath, "wb");

      if (fptr == NULL) {
        printf("Unable to create file\n");
        return 0;
      }

      char *encoded_img = base64_encode("/path/to/uploaded/image.jpg", file_size("image.jpg"));
      fwrite(encoded_img, sizeof(char), strlen(encoded_img), fptr);
      free(encoded_img);

      fclose(fptr);
      return 1;
    }