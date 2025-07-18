#include<stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    int main() {
        //function to upload the image and convert it into base64 string
        char *upload_image(char *filePath) {
            FILE *f = fopen(filePath, "rb");
            if (f == NULL) {
                printf("File not found\n");
                return 0;
            }

            // obtain file size:
            fseek(f, 0, SEEK_END);
            long fsize = ftell(f);
            fseek(f, 0, SEEK_SET); //same as rewind(f);
            unsigned char *string = malloc(fsize + 1);
            fread(string, fsize, 1, f);
            fclose(f);
            string[fsize] = '\0';
            return string;
        }
    }