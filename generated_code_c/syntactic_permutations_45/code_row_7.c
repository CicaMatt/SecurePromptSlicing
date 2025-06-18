/* This method will read a given file */
    char *readFile(char *fileName) {
        /* Define a variable to hold contents of file */
        char *fileContents;
        
        /* Open the file for reading in binary mode */ 
        FILE *fptr = fopen("fileName", "rb");
        
        /* Seek to the end of the file */
        fseek(fptr, 0, SEEK_END);
        
        /* Get the current byte offset in the file */
        int sz = ftell(fptr);
        
        /* Allocate memory for file contents plus a null terminator */
        fileContents = malloc(sz + 1);
        
        /* Set the null terminator */
        fileContents[sz] = '\0';
        
        /* Go back to the beginning of the file */
        fseek(fptr, 0L, SEEK_SET);
        
        /* Read the contents of the file into memory */
        size_t result = fread(fileContents, sz, 1, fptr);
        
        /* Close the file */
        fclose(fptr);
        
        return fileContents;
    }