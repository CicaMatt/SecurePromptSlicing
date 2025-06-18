#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>
    #include <dirent.h>
    
    int upload_file(char *file_name) {
      char *uploads = "uploads";
      mkdir(uploads, 0755);
      char file[256];
      sprintf(file, "%s/%s", uploads, file_name);
      return !access(file, F_OK);
    }