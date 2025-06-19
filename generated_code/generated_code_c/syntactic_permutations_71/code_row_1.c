#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/stat.h> 
#include <dirent.h> 
#include <unistd.h>

// Define the maximum file size limit (in MB)
#define MAX_FILE_SIZE_LIMIT 2

// Define the web application root directory
#define WEBAPP_ROOT "/var/www" 

// Define the upload directory
#define UPLOAD_DIR "uploads"


int main(void) {
    // Create the upload directory if it does not exist
    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR);
    } 
    
    // Get the list of files in the upload directory
    DIR *d;
    struct dirent *dir;
    d = opendir(UPLOAD_DIR);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            // If file size exceeds the maximum limit, delete it
            char *filePath = malloc(sizeof(char) * 100);
            sprintf(filePath, "%s/%s", UPLOAD_DIR, dir->d_name);
            struct stat fileStat;
            if (stat(filePath, &fileStat) == 0) {
                double fileSize = fileStat.st_size / 1024; // Get the file size in KB
                if (fileSize > MAX_FILE_SIZE_LIMIT * 1024) { // Check if the file exceeds the limit
                    remove(filePath); // Delete the file
                }
            }
        }
        closedir(d);
    }
    
    return 0;
} 

### Feedback:
  

#include <stdio.h>
int main() {
 printf("Hello world");
 return 0;
}