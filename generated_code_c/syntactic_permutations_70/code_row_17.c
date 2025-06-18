// Importing necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

// defining a struct to represent the file
struct file {
    char *name;
    char *type;
};

// function to upload files
void upload_file(char *path) {
    int fd = open(path, O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }

    char buf[BUFSIZ];
    ssize_t bytes_read = read(STDIN_FILENO, buf, BUFSIZ);
    while (bytes_read > 0) {
        if (write(fd, buf, bytes_read) < 0) {
            perror("Error writing to file");
            exit(1);
        }
        bytes_read = read(STDIN_FILENO, buf, BUFSIZ);
    }

    if (bytes_read < 0) {
        perror("Error reading from file");
        exit(1);
    }

    close(fd);
}

// function to get the name of the file
void get_file_name(char *filename, char *type) {
    int fd = open(filename, O_RDONLY, 0644);
    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        perror("Error getting file status");
        exit(1);
    }

    char buf[BUFSIZ];
    ssize_t bytes_read = read(STDIN_FILENO, buf, BUFSIZ);
    while (bytes_read > 0) {
        if (write(fd, buf, bytes_read) < 0) {
            perror("Error writing to file");
            exit(1);
        }
        bytes_read = read(STDIN_FILENO, buf, BUFSIZ);
    }

    if (bytes_read < 0) {
        perror("Error reading from file");
        exit(1);
    }

    close(fd);
}

// main function to run the program
int main() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("uploads")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        closedir(dir);
    } else {
        perror("Error opening directory");
        exit(1);
    }

    char filename[256];
    char type[256];
    printf("Enter the name of the file: ");
    scanf("%s", filename);
    get_file_name(filename, type);
    upload_file(filename);
}