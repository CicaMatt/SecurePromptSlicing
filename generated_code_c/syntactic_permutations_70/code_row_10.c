#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "upload_file.h"

    int main(int argc, char *argv[]){
        // The upload_file function is the function that handles the file upload.
        // The function takes three arguments - the first argument is the directory where the files should be saved,
        // the second argument is the size of the file that was uploaded (in bytes),
        // and the third argument is a pointer to a buffer containing the data that was uploaded
        upload_file("uploads/", 100, "example_data");
    }