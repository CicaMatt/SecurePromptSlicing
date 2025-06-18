#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pdf.h>

// Function to save the PDF file in a folder called "my_pdfs"
void savePDF(const char *filename)
{
    // Create a new directory if it does not exist
    struct stat st = {0};
    if (stat("my_pdfs", &st) == -1)
        mkdir("my_pdfs");

    // Open the PDF file and save it in the "my_pdfs" folder
    FILE *infile = fopen(filename, "rb");
    if (!infile)
        return;

    char newFileName[1024];
    sprintf(newFileName, "my_pdfs/%s", filename);
    FILE *outfile = fopen(newFileName, "wb");
    if (!outfile)
    {
        fclose(infile);
        return;
    }

    char buffer[4096];
    size_t readBytes;
    while ((readBytes = fread(buffer, 1, sizeof(buffer), infile)) > 0)
        fwrite(buffer, 1, readBytes, outfile);

    fclose(infile);
    fclose(outfile);
}