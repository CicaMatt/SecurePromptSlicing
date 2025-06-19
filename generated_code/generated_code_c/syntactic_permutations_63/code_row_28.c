#include<stdio.h>
    #include <string.h>
    #include <stdlib.h>

    struct FileData {
      char * buffer;
      int checksum;
    };

    struct FileData readFile(char * fileName) {
      FILE * fp = fopen(fileName, "r");
      if (fp == NULL) return -1;
      long lSize;
      fseek (fp , 0 , SEEK_END);
      lSize = ftell (fp);
      rewind (fp);

      char * buffer = malloc(lSize + 1);
      if (buffer == NULL) return -2;
      int checksum = 0;
      for (int i=0; i<lSize+1; i++) {
        buffer[i] = fgetc(fp);
        checksum += buffer[i];
      }

      struct FileData fileData;
      fileData.buffer = buffer;
      fileData.checksum = checksum;

      return fileData;
    }

    int saveFile(struct FileData *fileData, char *fileName) {
      FILE * fp = fopen(fileName, "w");
      if (fp == NULL) return -1;

      for (int i=0; i<sizeof(fileData->buffer); i++) {
        fputc(fileData->buffer[i], fp);
      }

      fclose(fp);
      return 0;
    }