#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#ifdef _WIN32
    #define PATH_SEP "\\"
#else
    #define PATH_SEP "/"
#endif

void create_dir(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

void unzip_file(const char *zip_path, const char *output_dir) {
    // Using system call to unzip as C standard library does not support ZIP handling
    char command[1024];
    snprintf(command, sizeof(command), "unzip -o \"%s\" -d \"%s\"", zip_path, output_dir);
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Error unzipping file.\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    const char *archive_name = "archive.zip";
    const char *output_directory = "/tmp/unpack";

    // Create the output directory if it does not exist
    create_dir(output_directory);

    // Unzip the archive to the specified directory
    unzip_file(archive_name, output_directory);

    return 0;
}


**Note:** This code assumes that `unzip` is installed on your system. If you're using a Windows environment, adapt the path separator and ensure that a compatible ZIP utility (like `7-Zip`) is available in your command line tools.