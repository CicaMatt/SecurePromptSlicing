#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    //Decorator for checking if the file exists in the images folder
     char *check_if_file_exists(char *file){
        FILE *fp;
         char path[1035];
        sprintf(path, "./images/%s", file);
        fp = fopen(path, "r");
        if (fp != NULL) {
            fclose(fp);
            return path;
        } else{
            return NULL;
        }
     }