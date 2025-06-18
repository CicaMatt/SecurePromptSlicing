#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main() {
        char fileName[256];
        FILE *file;
        printf("Enter file name\n");
        scanf("%s",fileName);

        file=fopen(fileName,"wb");

        if (file==NULL)
            return 1;

        fclose(file);
    }