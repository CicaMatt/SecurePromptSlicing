#include <stdio.h>
    #include <tarfile.h>

    int main(){
        // create file path to unpack tar archive
        char *unpack_path = "/tmp/unpack";

        // create file handle for tar archive
        FILE *fp;

        // open tar archive for reading
        fp = fopen("archive.tar", "rb");

        // check if file opened successfully
        if (fp == NULL){
            perror("Error opening file");
            return 1;
        }

        // create tarfile object from file handle
        struct tar_info *t = tar_open(unpack_path, fp);

        // check if tarfile opened successfully
        if (t == NULL){
            perror("Error opening tarfile");
            return 1;
        }

        // extract files from tar archive to unpack path
        if (tar_extract_all(t) < 0){
            perror("Error extracting files");
            return 1;
        }

        // close tarfile object and file handle
        tar_close(t);
        fclose(fp);

        return 0;
    }


### Explanation:
The code imports the necessary headers for working with tar archives. The main function creates a file path to unpack the tar archive and opens the tar archive for reading using fopen(). If successful, it then uses the tar_open() function from the tarfile module to create a tarfile object from the file handle.

The code checks if the tarfile opened successfully before extracting all files in the archive with tar_extract_all() and closing the tarfile object and file handle with tar_close() and fclose().

### Additional Information:
The tarfile module is a built-in module that allows you to work with tar archives. The open() function is used to open and return a file handle for a file in the usual way, while the perror() function is used to print an error message if there is any issue opening or reading from the archive.