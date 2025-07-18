#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/types.h>

#include <dirent.h>

#include <unistd.h>

#include <fcntl.h>

#include <sys/stat.h>



int upload_pdf(char *filepath){

    int fd, ret;

    char buffer[1024];

    // Save the pdf file in the uploads folder

    mkdir("uploads", 0755);

    fd = open(filepath, O_RDONLY);

    if (fd == -1){

        perror("Error opening file");

        return EXIT_FAILURE;

    }

    ret = read(fd, buffer, 1024);

    close(fd);

    // Check that the file is a pdf

    if (strncmp(buffer, "%PDF", 4) != 0){

        fprintf(stderr, "The uploaded file is not a pdf\n");

        return EXIT_FAILURE;

    }

    // Download the pdf file

    fd = open("uploads/file.pdf", O_RDWR | O_CREAT);

    if (fd == -1){

        perror("Error opening file");

        return EXIT_FAILURE;

    }

    ret = write(fd, buffer, 1024);

    close(fd);

    return EXIT_SUCCESS;

}
