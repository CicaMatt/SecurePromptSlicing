#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[]){
    DIR *dp;
    struct dirent *ep;
    dp = opendir ("/tmp/unpack");

    if (dp != NULL) {
        while ((ep = readdir (dp)) != NULL){
            printf("%s\n", ep->d_name);
        }
        closedir(dp);
    }else{
        perror("Unable to open directory");
    }
}