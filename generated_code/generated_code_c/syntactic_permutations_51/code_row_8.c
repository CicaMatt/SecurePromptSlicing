#include <stdio.h>  //standard input output header
#include <stdlib.h> //standard library header
#include <string.h> //string handling header
#include <errno.h>  //error numbering header
#include <fcntl.h>  //file control header
#include <unistd.h> //unix standard header
#include <sys/types.h>  //system data types header
#include <sys/stat.h>   //system status header
#include <archive.h>    //archive header
#include <archive_entry.h> //archive entry point header

int main() {
    char buffer[1024]; //buffer to store data
    int len;           //variable to store data length

    FILE *fp = fopen("test.tar.gz", "rb"); //open file in binary mode
    if (fp == NULL) {
        perror("fopen() error: ");
        return 1;
    }

    struct archive *a = archive_read_new();   //create new archive object
    archive_read_support_filter_gzip(a);      //add gzip support
    archive_read_support_format_tar(a);       //add tar format support
    if (archive_read_open_FILE(a, fp) != ARCHIVE_OK) {  //read tar file
        fprintf(stderr, "Can't read tar.gz file\n");
        archive_read_free(a);
        return 1;
    }

    struct archive_entry *entry; //entry to be extracted
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {  //loop through all entries in tar file
        char *filename = archive_entry_pathname(entry);       //extract filename from entry
        if (!strcmp(filename, "test.txt")) {                   //check if it's the desired file
            int fd = open("/tmp/unpack", O_WRONLY | O_CREAT, 0644); //open output file
            if (fd == -1) {
                perror("open() error: ");
                return 1;
            }
            while (len = archive_read_data(a, buffer, sizeof(buffer))) {    //extract data from entry
                write(fd, buffer, len);   //write extracted data to output file
            }
            close(fd);                    //close output file
        }
    }
    
    archive_read_free(a);  //free archive object
    fclose(fp);            //close input file

    return 0;
}