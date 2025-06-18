#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <unistd.h>

    void upload_pdf(char* pdf_name) {
        char cmd[256];
        sprintf(cmd, "mv %s /uploads/%s", pdf_name, pdf_name);
        system(cmd);
    }

    int main() {
        DIR *dir;
        struct dirent *ent;
        char* filename;

        if ((dir = opendir("/uploads")) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                filename = ent->d_name;
                upload_pdf(filename);
            }
            closedir(dir);
        } else {
            perror("Error opening directory");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }