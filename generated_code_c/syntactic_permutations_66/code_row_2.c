#include <stdio.h>
#include <stdlib.h>

// The function below will save the uploaded PDF files to uploads folder
void save_pdf(char *file)
{
    FILE *fp;
    char str[256];

    // Open the file for writing
    fp = fopen("uploads/", "wb");
    if (!fp)
    {
        perror("Unable to open the file");
        exit(EXIT_FAILURE);
    }

    // Write the file contents to the file.
    while (fgets(str, 256, file))
    {
        fputs(str, fp);
    }

    if (ferror(file) || ferror(fp))
    {
        perror("Error reading or writing files");
        exit(EXIT_FAILURE);
    }

    // Close the file.
    if (fclose(fp))
    {
        perror("Unable to close the file");
        exit(EXIT_FAILURE);
    }
}