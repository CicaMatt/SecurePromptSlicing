#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    // Upload handler
    void handle_upload(const char *file, const char *content) {
        FILE *f;
        f = fopen(file, "w");
        if (f == NULL) {
            printf("Failed to open file!");
            return;
        }
        
        if (fwrite(content, 1, strlen(content), f) != strlen(content)) {
            printf("Failed to write file!");
            fclose(f);
            return;
        }
        
        printf("File saved successfully!");
    }