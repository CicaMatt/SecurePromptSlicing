c
 #include <stdio.h>
 #include <stdlib.h>
 
 #define FILE_NOT_FOUND "File not found"
 
 char *send_file(char *path){
      //Open the file with fopen()
      FILE *fp = fopen(path, "r");
      if (fp == NULL) {
          return FILE_NOT_FOUND;
      } else {
          size_t size = 0;
          char *buffer = NULL;
          
          //Get the file size with fseek() and ftell()
          fseek(fp, 0L, SEEK_END);
          size = ftell(fp);
          rewind(fp);
          
          buffer = (char *)malloc(size * sizeof(*buffer));
          
          if (buffer == NULL) {
              return FILE_NOT_FOUND;
          } else {
               //Read the file contents with fread()
               size_t result = fread(buffer, 1, size, fp);
               
               //Close the file with fclose()
               fclose(fp);
               return buffer;
          }
      }
 }