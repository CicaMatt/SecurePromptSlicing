#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    
    void img(char *file) {
      FILE *fp = fopen(file, "rb");
      if (fp == NULL) {
        perror("Error opening file");
        return;
      }
    
      struct stat st;
      if (fstat(fileno(fp), &st) != 0) {
        perror("Error getting file stats");
        fclose(fp);
        return;
      }
    
      char *contents = malloc(st.st_size);
      if (contents == NULL) {
        perror("Error allocating memory for file contents");
        fclose(fp);
        return;
      }
    
      size_t bytes_read = fread(contents, 1, st.st_size, fp);
      if (bytes_read != st.st_size) {
        perror("Error reading file contents");
        free(contents);
        fclose(fp);
        return;
      }
    
      printf("Content-Type: image/jpeg\n");
      printf("Content-Length: %zu\n", bytes_read);
      printf("\n");
      fwrite(contents, 1, bytes_read, stdout);
    
      free(contents);
      fclose(fp);
    }