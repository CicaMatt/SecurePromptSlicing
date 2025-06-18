#include <stdlib.h>
    #include <stdio.h>
    int main() {
        // Create file pointer to read/write the file
        FILE *file;
        char *filename = "uploads/sample.pdf";
        file = fopen(filename, "w");
    
        // Read the pdf file contents and save it to a string buffer
        char buffer[1024];
        int read;
        while ((read = getchar()) != EOF) {
            buffer[read] = (char) read;
        }
        
        // Save the contents of the string buffer to the file
        fwrite(buffer, sizeof(buffer), 1, file);
    
        // Close file pointer and return success code
        fclose(file);
        return 0;
    }