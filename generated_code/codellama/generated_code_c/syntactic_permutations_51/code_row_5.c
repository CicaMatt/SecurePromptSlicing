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
