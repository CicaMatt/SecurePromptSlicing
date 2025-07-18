#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // accept pdf file from user
    FILE *pdf_file;
    char pdf_name[1024];
    printf("Enter PDF file name: ");
    scanf("%s", &pdf_name);

    // open file for reading
    pdf_file = fopen(pdf_name, "r");

    if (pdf_file == NULL) {
        printf("Failed to read file\n");
        return 1;
    }

    // get file size
    fseek(pdf_file, 0L, SEEK_END);
    int pdf_size = ftell(pdf_file);
    rewind(pdf_file);

    // allocate memory for content
    char *pdf_content;
    pdf_content = (char *)malloc((pdf_size + 1) * sizeof(char));

    if (pdf_content == NULL) {
        printf("Failed to allocate memory\n");
        fclose(pdf_file);
        return 2;
    }

    // read content from file
    size_t bytes_read = fread(pdf_content, sizeof(char), pdf_size, pdf_file);

    if (bytes_read != pdf_size) {
        printf("Failed to read all data\n");
        free(pdf_content);
        fclose(pdf_file);
        return 3;
    }

    // terminate string with null character
    pdf_content[bytes_read] = '\0';

    // close file
    fclose(pdf_file);

    // extract text from PDF content
    char *text = (char *)malloc((pdf_size + 1) * sizeof(char));
    if (text == NULL) {
        printf("Failed to allocate memory\n");
        free(pdf_content);
        return 4;
    }

    int i, j;
    for (i = 0, j = 0; i < pdf_size; i++) {
        if (pdf_content[i] >= '!' && pdf_content[i] <= '~') {
            text[j++] = pdf_content[i];
        }
    }

    // terminate string with null character
    text[j] = '\0';

    // print extracted text
    printf("Extracted text:\n%s\n", text);

    // free memory
    free(pdf_content);
    free(text);

    return 0;
}