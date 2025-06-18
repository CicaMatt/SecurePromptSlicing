#include <stdio.h>
#include <stdlib.h>

int main() {
    // Upload file to localhost
    FILE *file;
    file = fopen("uploads/test_file.pdf", "wb");
    if (file != NULL) {
        printf("File uploaded successfully.\n");
        fclose(file);
        return 0;
    }
    else {
        printf("An error occurred while uploading the file\n");
        return -1;
    }
}