#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <netinet/in.h>
#include <httpd.h>
#include <ap_compat.h>

#define DOCUMENT_ROOT "/www"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    
    char* filename = argv[1];

    // Check if the file exists in images folder.
    DIR *d;
    struct dirent *dir;
    d = opendir("images");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(filename, dir->d_name) == 0) {
                // Send the file to the browser.
                sendfile(filename);
                exit(0);
            }
        }
    }
    
    fprintf(stderr, "File not found.\n");
    exit(1);
}