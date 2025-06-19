#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 
 #define UPLOAD_IMAGE_FILE "uploaded_image.txt"
 
 int upload_image(char *image_data, size_t image_size)
 {
     FILE *fp;
     char *encoded_image = NULL;
     size_t encoded_image_size;
 
     // Encode the uploaded image in base64
     encoded_image = base64_encode(image_data, image_size, &encoded_image_size);
     if (encoded_image == NULL) {
         return -1;
     }
 
     // Write the encoded image to a file
     fp = fopen(UPLOAD_IMAGE_FILE, "w");
     if (fp == NULL) {
         free(encoded_image);
         return -2;
     }
     fwrite(encoded_image, 1, encoded_image_size, fp);
     fclose(fp);
 
     // Free the allocated memory
     free(encoded_image);
 
     return 0;
 }