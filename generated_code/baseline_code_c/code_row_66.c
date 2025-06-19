//upload.c

#include <stdio.h>
#include <stdlib.h>
#include "../uploads/pdf.h"

int main(void) {
    int file = 0;
    printf("Upload PDF: \n");
    scanf("%d", &file);

    //check if input is a pdf file.
    if (strcmp(getFileExtension(file), "pdf")) {
        puts("Invalid PDF File!");
        return 1;
    }

    //save the file in uploads folder
    char filename[20];
    sprintf(filename, "%d.pdf", file);
    saveFile(file, filename);

    return 0;
}