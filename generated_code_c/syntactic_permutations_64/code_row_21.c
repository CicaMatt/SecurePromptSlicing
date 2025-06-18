#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upload_pdf() {
    char filename[50];
    FILE *fptr;

    printf("Enter the name of the pdf file: ");
    scanf("%s", filename);

    fptr = fopen(filename, "w");

    if (fptr == NULL) {
        perror("Failed to open file");
        return;
    }

    printf("File saved in uploads folder\n");
}