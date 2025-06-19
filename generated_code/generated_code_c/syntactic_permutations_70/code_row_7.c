c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#define MAX_FILENAME 256
#define UPLOADS_DIRECTORY "/uploads"
void upload_file(const char* filename);
int main(int argc, char** argv) {
    // Get the file name from command line
    const char* filename = argv[1];
    if (filename == NULL) {
        printf("No file specified\n");
        return 0;
    }
    upload_file(filename);
    return 0;
}
void upload_file(const char* filename) { 
    // Open the file to read
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }
    char buf[1024]; 
    memset(buf, 0, 1024);
    fread(buf, 1024, 1, f); 
    int size = ftell(f); 
    if (size == -1) {
        printf("Unable to determine file size\n");
        return;
    }
    // Open the uploads directory
    DIR *dir = opendir(UPLOADS_DIRECTORY);
    if (dir == NULL) {
        printf("Unable to open uploads directory %s\n", UPLOADS_DIRECTORY);
        return;
    }
    // Create a new file in the uploads directory
    char path[MAX_FILENAME];
    strcpy(path, UPLOADS_DIRECTORY "/");
    int len = strlen(UPLOADS_DIRECTORY) + 1;
    strncpy(path + len, filename, MAX_FILENAME - len);
    FILE *of = fopen(path, "wb"); 
    if (of == NULL) {
        printf("Unable to create file %s\n", path);
        return;
    }
    // Copy the contents of the source file to the destination file
    while (!feof(f)) {
        fwrite(buf, 1024, 1, of); 
        size -= 1024;
    }
    // Close files and directories
    fclose(f);
    fclose(of);
    closedir(dir);
}