#include <tarfile.h>
#include <stdio.h> 

int main(void) {
    char *filename = "/path/to/myfile.tar.gz";
    FILE *fp;

    // Open the file in binary read mode
    fp = fopen(filename, "rb");

    if (fp != NULL) {
        // Create a tar object from the file
        TarFile *tf = tarfile_open(NULL, fp);

        if (tf != NULL) {
            char target[2048];

            // Extract the files to /tmp/unpack
            strcpy(target, "/tmp/unpack");

            // Extract the contents of the tar file
            tarfile_extractall(tf, target);
        }
    } else {
        printf("Failed to open %s\n", filename);
    }
}