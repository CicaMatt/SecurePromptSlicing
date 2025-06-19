#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pdf_parser.h"

// function to save the pdf file in the uploads folder
void save_file(const char* filename, const char* file_data){
    FILE *file = fopen("uploads/" + filename, "w");
    if (file == NULL) {
        printf("Unable to create file\n");
        exit(1);
    }

    // save the file data in the newly created file
    fwrite(file_data, sizeof(char), strlen(file_data), file);
    printf("File saved successfully\n");
    
    fclose(file);
}

// function to handle the pdf files
void process_pdf(const char* file_name){
    // get the file data of the pdf file
    const char* file_data = get_pdf_data(file_name);
    if (file_data == NULL) {
        printf("Unable to read PDF file\n");
        exit(1);
    }
    
    // save the pdf file in the uploads folder
    save_file(file_name, file_data);
}