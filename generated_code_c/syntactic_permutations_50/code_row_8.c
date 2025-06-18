#include <tarfile.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    int main(){
        //Open the archive.zip file as a tarfile.
        char *tar_name = "/tmp/archive.zip";
        struct stat st;
        if(lstat(tar_name, &st) == -1){
            perror("lstat");
            exit(EXIT_FAILURE);
        }
        int tarfd = open(tar_name, O_RDONLY);
        if(tarfd == -1){
            perror("open");
            exit(EXIT_FAILURE);
        }
        //Extract files from the archive to the /tmp/unpack directory.
        char *dir_name = "/tmp/unpack";
        struct tarfile *tar;
        int err;
        if((tar = tarfile_open(NULL, dir_name)) == NULL){
            fprintf(stderr, "Cannot open tar archive\n");
            exit(EXIT_FAILURE);
        }
        for (;;) {
            struct tarfile *t;
            if ((t = tarfile_next(tar)) == NULL) {
                break;
            }
            char buff[BUFSIZ];
            int n;
            while((n = tarfile_read(t, buff, sizeof(buff))) > 0){
                write(STDOUT_FILENO, buff, n);
            }
        }
        tarfile_close(tar);
    }