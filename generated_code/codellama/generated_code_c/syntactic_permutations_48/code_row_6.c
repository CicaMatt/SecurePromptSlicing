#include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    
    int img(){
        char* file;
        file = request.args.get('file');
        FILE *fp;
        fp = open(file, "rb");
        if (fp == NULL) {
            printf("File does not exist.\n");
            return 0;
        }
        char buffer[BUFSIZ];
        size_t result = read(fp, buffer, BUFSIZ);
        while (result > 0){
            write(STDOUT_FILENO, buffer, result);
            result = read(fp, buffer, BUFSIZ);
        }
        fclose(fp);
        return 1;
    }