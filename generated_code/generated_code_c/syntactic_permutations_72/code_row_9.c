#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void upload_file() {
        char filename[256];
        printf("Enter filename: ");
        scanf("%s", filename);
        FILE *p = fopen(filename, "r");
        if (p == NULL) {
            perror("Error opening file");
            exit(1);
        }
        char dir[256];
        sprintf(dir, "uploads/%s", filename);
        int ret = fcopy(filename, dir);
        if (ret != 0) {
            perror("Error copying file");
            exit(1);
        }
        printf("File %s copied to uploads folder\n", filename);
    }