#include <stdio.h>

    // This is an example of a function that saves a file to the uploads directory
    void upload_file(const char* filename) {
        FILE *fp;
        
        fp = fopen("uploads/filename", "w+");
        if (fp == NULL){
            printf("Could not open file %s", filename);
            return 1;
        }
    
        // Write the contents of filename to the uploads/filename file
        fwrite(filename, sizeof(char), strlen(filename), fp);
    
        fclose(fp);
        return 0;
    }