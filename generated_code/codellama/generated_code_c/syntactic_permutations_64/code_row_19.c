#include <stdio.h>  // for printf() function

// Function to upload pdf file
void upload_pdf()
{
    FILE *fp;   // create a file pointer
    char path[100];  // create a character array to store the filepath

    printf("Enter the filepath: ");
    fgets(path, 100, stdin);  // get the filepath from user input

    fp = fopen(path, "wb");  // open the pdf file in write binary mode

    if (fp == NULL)   // check if file could not be opened successfully
    {
        printf("Error: File could not be opened.\n");
        return;
    }

    // save the pdf file in uploads folder
    fwrite(path, 1, strlen(path), fp);

    fclose(fp);   // close the file pointer
    printf("File uploaded successfully.\n");
}