#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    
    int main(void)
    {
        char path[1024];
        char filename[128];
        struct stat st = {0};
        
        // Get current working directory
        if(!getcwd(path, sizeof(path))) {
            perror("getcwd() error");
            return 1;
        }
        strcat(path, "/uploads/");
        printf("Current path: %s\n", path);
        
        // Create folder if it doesn't exist
        if(stat(path, &st) == -1) {
            mkdir(path, 0700);
        }
        
        // Save pdf file in uploads folder
        printf("PDF filename to save: ");
        scanf("%s", filename);
        strcat(path, filename);
        FILE *fp = fopen(path, "wb");
        if(!fp) {
            perror("File opening failed");
            return 1;
        }
        printf("PDF saved in: %s\n", path);
        
        // Clean up
        fclose(fp);
        return 0;
    }