//Including header files for all necessary dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarfile.h"
#include "gzip.h"
#include "bz2.h"

//Function definition for the decompress function
int decompress(char *file_path) {
    //Defining variables
    int status;
    char *dest_dir = "/tmp/unpack";

    //Checking if the file exists
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Unable to open the file");
    }

    //Opening the tarball and extracting its contents
    status = untar(file_path, dest_dir);
    if (status != 0) {
        fprintf(stderr, "Failed to extract the contents of %s\n", file_path);
    }
    
    //Closing the tarball
    fclose(file);

    return status;
}

//Function definition for the main function
int main() {
    char *file_path = "tar.gz";
    int status = decompress(file_path);

    if (status != 0) {
        fprintf(stderr, "Failed to decompress %s\n", file_path);
    }
    
    return status;
}