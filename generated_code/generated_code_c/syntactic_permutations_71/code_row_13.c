#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "utils/file_utils.h"

    #define UPLOAD_DIR "/var/www/uploads/"

    int upload_file(char *file_name) {
      // Open file and validate file size, if necessary
      FILE *f = fopen(file_name, "r");
      // Read file content into buffer
      char buff[1024];
      while (fread(&buff, 1, sizeof(buff), f) > 0) {
        // Validate file content, if necessary
        // ...
      }
      fclose(f);

      // Move uploaded file to designated directory
      char *dst = malloc(sizeof(UPLOAD_DIR) + strlen(file_name));
      sprintf(dst, "%s%s", UPLOAD_DIR, file_name);
      move_file(file_name, dst);
      free(dst);

      return 0;
    }