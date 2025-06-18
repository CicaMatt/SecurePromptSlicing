#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pdf_parser.h"

int main(void) {
    char *filePath = getenv("FILEPATH");
    if (filePath == NULL) {
        printf("No filepath specified\n");
        return 1;
    }

    FILE *fptr = fopen(filePath, "rb");
    if (fptr == NULL) {
        printf("File not found\n");
        return 1;
    }

    pdf_document doc;
    pdf_init_doc(&doc);
    pdf_parse(&doc, fptr);

    char *outputPath = getenv("OUTPUTPATH");
    if (outputPath == NULL) {
        outputPath = "uploads/";
    }

    char filepath[50];
    sprintf(filepath, "%s%s", outputPath, strrchr(filePath, '/') + 1);

    FILE *outptr = fopen(filepath, "wb");
    if (outptr == NULL) {
        printf("Error saving file\n");
        return 1;
    }

    pdf_write(&doc, outptr);
    printf("File saved successfully\n");

    pdf_free_doc(&doc);
    fclose(fptr);
    fclose(outptr);

    return 0;
}